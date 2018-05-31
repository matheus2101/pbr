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

    intersection_result = bvh_->intersect(ray, intersection_record);

    return intersection_result;
}

void Scene::buildBVH(void)
{
    bvh_ = new BVH(primitives_);
}

void Scene::load(void)
{

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
        std::cout << mesh->mName.C_Str() << " " << j << std::endl;

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

            if (j == 2) {
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{r, g, b},
                                                                                 glm::vec3{100.0, 100.0, 100.0})));
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
