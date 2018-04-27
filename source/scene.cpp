#include "scene.h"
#include <ctime>
#include <cstdlib>
#include <random>

Scene::Scene(void)
{
}

Scene::~Scene(void)
{
}

bool Scene::intersect(const Ray &ray,
                      IntersectionRecord &intersection_record) const
{
    bool intersection_result = false;
    IntersectionRecord tmp_intersection_record;
    std::size_t num_primitives = primitives_.size();

    // Loops over the list of primitives, testing the intersection of each primitive against the given ray
    for (std::size_t primitive_id = 0; primitive_id < num_primitives; primitive_id++)
        if (primitives_[primitive_id]->intersect(ray, tmp_intersection_record))
            if ((tmp_intersection_record.t_ < intersection_record.t_) && (tmp_intersection_record.t_ > 0.0))
            {
                intersection_record = tmp_intersection_record;
                intersection_result = true; // the ray intersects a primitive!
            }

    return intersection_result;
}

void Scene::load(void)
{
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.5f, 0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{1.0f, 1.0f, 1.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, 0.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 5.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec3{0.0f, 2.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 1.0f}, glm::vec3{7.0f, 0.0f, 2.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.5f, 0.5f, -0.5f}, glm::vec3{0.0f, 1.0f, 1.0f}, glm::vec3{0.0f, 3.0f, 10.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, 0.5f, -0.5f}, glm::vec3{1.0f, 1.0f, 0.0f}, glm::vec3{0.0f, 1.0f, 6.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec3{1.0f, 1.0f, 1.0f}, glm::vec3{0.0f, 4.0f, 3.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));
    // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec3{6.0f, 3.0f, 1.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 0.2f}));

    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle(glm::vec3{  0.5f, 0.5f,  0.0f },
    // glm::vec3{ -1.25f, 0.0f, 0.0f }, glm::vec3{  0.0f,-1.25f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f})));

    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle(glm::vec3{  0.0f, 0.0f,  0.0f },
    // glm::vec3{ 0.5f, 0.0f, 0.0f }, glm::vec3{  0.0f,0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f})));

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile("obj/cornellbox.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

    if (!scene)
    {
        std::cerr << "Não foi possível importar o arquivo" << std::endl;
    }

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];
        // std::cout << mesh->mName.C_Str() << std::endl;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);

        double r = dist(mt), g = dist(mt), b = dist(mt);

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            if (j == 6) {
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{r, g, b},
                                                                                 glm::vec3{10.0, 10.0, 10.0})));
            } else {
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{r, g, b},
                                                                                 glm::vec3{0.0, 0.0, 0.0})));
            }
        }
    }
}
