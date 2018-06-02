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

    const aiScene *scene = importer.ReadFile("obj/CornellBox-Sphere.obj",
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

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            if (j == 7) { // lamp
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 1.0f, 1.0f},
                                                                                 glm::vec3{10.0, 10.0, 10.0},
                                                                                 Type::DIFFUSE
                                                                                 )));
            } else if ((j == 4) || (j == 3)) { // walls & ceiling
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 1.0f, 1.0f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            } else if (j == 2) { // floor
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 5)
            { // right wall
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.161f, 0.133f, 0.427f},
                                                                                 glm::vec3{0.161f, 0.133f, 0.427f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 6)
            { // left wall
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.427f, 0.133f, 0.161f},
                                                                                 glm::vec3{0.427f, 0.133f, 0.161f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 1)
            { // short box
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{1.0f, 0.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 0.0f, 0.0f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 0)
            { // tall box
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 0.0f, 1.0f},
                                                                                 glm::vec3{0.0f, 0.0f, 1.0f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::MIRROR)));
            }
            else
            {
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 0.0f, 0.0f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
        }
    }
}
