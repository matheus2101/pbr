#include "raytracer.h"
#include "onb.h"
#include <random>
#include <omp.h>
#include <glm/glm.hpp>
#include <cmath>

unsigned num_samples = 1000;
unsigned max_depth = 10;

RayTracer::RayTracer(Camera &camera,
                     const Scene &scene,
                     const glm::vec3 background_color,
                     Buffer &buffer) : camera_(camera),
                                       scene_(scene),
                                       background_color_{background_color},
                                       buffer_(buffer)
{
}

glm::vec3 RayTracer::cook_torrance(glm::vec3 incident, glm::vec3 outgoing, IntersectionRecord intersection_record)
{
    // convert to double precision
    glm::dvec3 wi = glm::dvec3{incident};
    glm::dvec3 wo = glm::dvec3{outgoing};
    glm::dvec3 n = glm::dvec3{intersection_record.normal_};

    wo = -wo;
    glm::dvec3 h = glm::normalize(wo + wi);
    double nh = glm::abs(glm::dot(n, h));
    double nwo = glm::abs(glm::dot(n, wo));
    double nwi = glm::abs(glm::dot(n, wi));
    double hwo = glm::abs(glm::dot(h, wo));
    double hwi = glm::abs(glm::dot(h, wi));

    // beckmann

    double m = 0.3;
    double nh2 = nh * nh;
    double m2 = m * m;

    double d1 = 1.0 / ( M_PI * m2 * nh2 * nh2 );
    double d2 = ( nh2 - 1.0 ) / ( m2 * nh2 );
    double D = d1 * exp( d2 );

    // geometric term

    double g1 = 2.0 * nh / hwo;
    double G = glm::min(1.0, glm::min(g1 * nwo, g1 * nwi));

    // fresnel term
    glm::dvec3 R0 = M_PI * glm::dvec3{intersection_record.brdf_};
    glm::dvec3 F = R0 + (glm::dvec3(1.0) - R0) * pow((1.0 - hwi), 5);

    // cock-Torrance
    glm::dvec3 ct = (F * G * D) / (4.0 * nwo * nwi);

    // pdf
    // double pdf = nh / (4.0 * hwi);
    double om = glm::abs( glm::dot( wi, h ) );
    double pdf = ( d1 * exp( d2 ) * nh ) / ( 4.0 * om );

    return (ct / pdf);
}

float RayTracer::schlick(glm::vec3 incident, glm::vec3 normal, float n1, float n2)
{
    float Ro = (n1 - n2) / (n1 + n2);
    Ro *= Ro;
    float cosX = -glm::dot(normal, incident);
    
    if (n1 > n2)
    {
        float n = n1 / n2;
        float cosT2 = 1.0 - n * n * (1.0 - cosX * cosX);
        if (cosT2 < 0.0) return 1.0;
        cosX = sqrt(cosT2);
    }

    float x = 1.0 - cosX;
    return Ro + (1.0 - Ro) * powf(x, 5);
}

void RayTracer::integrate(void)
{

    std::uniform_real_distribution<float> dis[16];
    std::mt19937 gen[16];

    for (int i = 0; i < 16; i++)
    {
        std::random_device rd;       //Will be used to obtain a seed for the random number engine
        gen[i] = std::mt19937(rd()); //Standard mersenne_twister_engine seeded with rd()
        dis[i] = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }

// Image space origin (i.e. x = 0 and y = 0) at the top left corner.
#pragma omp parallel for schedule(dynamic, 5)

    // Loops over image rows
    for (std::size_t y = 0; y < buffer_.v_resolution_; y++)
    {
        std::stringstream progress_stream;
        progress_stream << "\r  progress .........................: "
                        << std::fixed << std::setw(6)
                        << std::setprecision(2)
                        << 100.0 * y / (buffer_.v_resolution_ - 1)
                        << "%";

        std::clog << progress_stream.str();

        // Loops over image columns
        for (std::size_t x = 0; x < buffer_.h_resolution_; x++)
        {

            for (unsigned i = 0; i < num_samples; i++)
            {

                double rand_x = dis[omp_get_thread_num()](gen[omp_get_thread_num()]);
                double rand_y = dis[omp_get_thread_num()](gen[omp_get_thread_num()]);

                Ray ray{camera_.getWorldSpaceRay(glm::vec2{x + rand_x, y + rand_y})};

                buffer_.buffer_data_[x][y] += L(ray, 0);
            }

            buffer_.buffer_data_[x][y] /= static_cast<float>(num_samples);
        }
    }

    std::clog << std::endl;
}

glm::vec3 RayTracer::L(Ray &ray, unsigned depth)
{
    glm::vec3 L0{0.0f, 0.0f, 0.0f};
    IntersectionRecord intersection_record;
    intersection_record.t_ = std::numeric_limits<double>::max();

    if (depth < max_depth)
    {
        if (scene_.intersect(ray, intersection_record))
        {
            if (intersection_record.type_ == Type::DIFFUSE)
            {
                Ray refl_ray = intersection_record.get_new_ray();

                float cos_ = glm::dot(refl_ray.direction_, intersection_record.normal_);

                if (cos_ < 0)
                {
                    refl_ray.direction_ = -refl_ray.direction_;
                    cos_ = -cos_;
                }

                if (intersection_record.emittance_ == glm::vec3{0.0f, 0.0f, 0.0f})
                {
                    L0 = intersection_record.emittance_ + 2.0f * ((float)M_PI) * intersection_record.brdf_ *
                                                              L(refl_ray, ++depth) * cos_;
                }
                else
                {
                    L0 = intersection_record.emittance_ + 2.0f * ((float)M_PI) * intersection_record.brdf_ * cos_;
                }
            }
            else if (intersection_record.type_ == Type::MIRROR)
            {
                Ray refl_ray = intersection_record.get_reflection(ray);

                L0 = L(refl_ray, ++depth);
            }
            else if (intersection_record.type_ == Type::METAL)
            {
                Ray refl_ray = intersection_record.importance_sampling(ray.direction_, 0.3f);
                L0 = intersection_record.emittance_ + glm::vec3(cook_torrance(refl_ray.direction_, ray.direction_, intersection_record)) *
                                                          L(refl_ray, ++depth) * glm::dot(intersection_record.normal_, refl_ray.direction_);
            }
            else if (intersection_record.type_ == Type::GLASS)
            {
                float cos_ = glm::dot(ray.direction_, intersection_record.normal_);
                float random = prng.get_rand(omp_get_thread_num());
                float n1, n2;

                if (cos_ < 0.0f)
                {
                    n1 = 1.0f;
                    n2 = 1.5f;
                }
                else
                {
                    n1 = 1.5f;
                    n2 = 1.0f;
                    intersection_record.normal_ = -intersection_record.normal_;
                }

                float schlick_ = schlick(ray.direction_, intersection_record.normal_, n1, n2);
                Ray new_ray;

                if (random < schlick_) {
                    new_ray = intersection_record.get_reflection(ray);
                    // new_ray = intersection_record.importance_sampling(ray.direction_, 1.0f);
                } else
                {
                    new_ray = intersection_record.get_refraction(ray, n1, n2);
                }
                L0 = L(new_ray, ++depth);
            }
        }
    }

    return L0;
}