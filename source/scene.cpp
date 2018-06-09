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

void Scene::loadFinalScene(void)
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile("obj/breakfast_room/paredes.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/quadro.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{12.0, 12.0, 12.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/mesa.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::GLASS)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/suporte_mesa.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/pes_mesa.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/cadeiras.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.75f, 0.1f, 0.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/suporte_lampada1.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.1f, 0.1f, 0.8f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/suporte_lampada2.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.75f, 0.1f, 0.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/enfeite_lampada1.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.3f, 0.6f, 0.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/enfeite_lampada2.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.3f, 0.6f, 0.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/luminaria1.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.85f, 0.85f, 0.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/luminaria2.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{0.0f, 0.85f, 0.85f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/teapot.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::METAL)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/xicaras.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/pratos.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/colheres.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::METAL)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/jarra.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/pes_cadeiras.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }

    scene = importer.ReadFile("obj/breakfast_room/persiana.obj",
                              aiProcess_CalcTangentSpace |
                                  aiProcess_Triangulate |
                                  aiProcess_JoinIdenticalVertices |
                                  aiProcess_SortByPType);

    for (unsigned int j = 0; j < scene->mNumMeshes; j++)
    {
        auto mesh = scene->mMeshes[j];

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            auto face = mesh->mFaces[i];

            auto v1 = mesh->mVertices[face.mIndices[0]];
            auto v2 = mesh->mVertices[face.mIndices[1]];
            auto v3 = mesh->mVertices[face.mIndices[2]];

            primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                             glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                             glm::vec3{0.0f, 1.0f, 0.0f},
                                                                             glm::vec3{1.0f, 1.0f, 1.0f},
                                                                             glm::vec3{0.0, 0.0, 0.0},
                                                                             Type::DIFFUSE)));
        }
    }
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

            if (j == 7)
            { // lamp
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{1.0f, 1.0f, 1.0f},
                                                                                 glm::vec3{12.0, 12.0, 12.0},
                                                                                 Type::DIFFUSE)));
            }
            else if ((j == 4) || (j == 3))
            { // walls & ceiling
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{0.75f, 0.75f, 0.75f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 2)
            { // floor
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.0f, 1.0f, 0.0f},
                                                                                 glm::vec3{0.75f, 0.75f, 0.25f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 5)
            { // right wall
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.25f, 0.25f, 0.75f},
                                                                                 glm::vec3{0.25f, 0.25f, 0.75f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 6)
            { // left wall
                primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                                 glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                                 glm::vec3{0.75f, 0.25f, 0.25f},
                                                                                 glm::vec3{0.75f, 0.25f, 0.25f},
                                                                                 glm::vec3{0.0, 0.0, 0.0},
                                                                                 Type::DIFFUSE)));
            }
            else if (j == 1)
            { // short box
                // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                //                                                                  glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                //                                                                  glm::vec3{1.0f, 0.0f, 0.0f},
                //                                                                  glm::vec3{1.0f, 0.0f, 0.0f},
                //                                                                  glm::vec3{0.0, 0.0, 0.0},
                //                                                                  Type::GLASS)));
            }
            else if (j == 0)
            { // tall box
                // primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                //                                                                  glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                //                                                                  glm::vec3{0.0f, 0.0f, 1.0f},
                //                                                                  glm::vec3{1.0f, 0.0f, 1.0f},
                //                                                                  glm::vec3{0.0, 0.0, 0.0},
                //                                                                  Type::GLASS)));
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

        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere(glm::vec3{-0.3f, 0.30f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f},
                                                                       glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, Type::GLASS, 0.3f)));

        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Sphere(glm::vec3{-0.3f, 0.30f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f},
                                                                       glm::vec3{0.7f, 0.3f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, Type::DIFFUSE, 0.28f)));
    }
}
