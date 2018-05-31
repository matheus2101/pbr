#include "raytracer.h"
#include "onb.h"
#include <random>
#include <omp.h>

unsigned num_samples = 3000;
unsigned max_depth = 5;

RayTracer::RayTracer(Camera &camera,
                     const Scene &scene,
                     const glm::vec3 background_color,
                     Buffer &buffer) : camera_(camera),
                                       scene_(scene),
                                       background_color_{background_color},
                                       buffer_(buffer)
{
}

void RayTracer::integrate(void)
{

    std::uniform_real_distribution<float> dis[16];
    std::mt19937 gen[16];

    for (int i = 0; i < 16; i++)
    {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
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

            buffer_.buffer_data_[x][y] /= static_cast<float> (num_samples);
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
            Ray refl_ray = intersection_record.get_new_ray();

            L0 = intersection_record.emittance_ + 2.0f * ((float)M_PI) * intersection_record.brdf_ *
                                                      L(refl_ray, ++depth) * glm::dot(intersection_record.normal_, refl_ray.direction_);
        }
    }

    return L0;
}