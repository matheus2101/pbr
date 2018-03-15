#include "scene.h"
#include <ctime>
#include <cstdlib>

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
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f,  0.0f }, glm::vec3{1.0f, 0.0f, 0.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f,  0.0f }, glm::vec3{0.0f, 1.0f, 0.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f,  0.0f }, glm::vec3{0.0f, 0.0f, 1.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f,  0.0f }, glm::vec3{1.0f, 0.0f, 1.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f, 0.5f, -0.5f }, glm::vec3{0.0f, 1.0f, 1.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f, 0.5f, -0.5f }, glm::vec3{1.0f, 1.0f, 0.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{  0.5f,-0.5f, -0.5f }, glm::vec3{1.0f, 1.0f, 1.0f}, 0.2f } ) );
    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Sphere{ glm::vec3{ -0.5f,-0.5f, -0.5f }, glm::vec3{0.5f, 0.5f, 0.5f}, 0.2f } ) );

    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle(glm::vec3{  0.5f, 0.5f,  0.0f },
    // glm::vec3{ -1.25f, 0.0f, 0.0f }, glm::vec3{  0.0f,-1.25f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f})));

    // primitives_.push_back( Primitive::PrimitiveUniquePtr( new Triangle(glm::vec3{  0.0f, 0.0f,  0.0f },
    // glm::vec3{ 0.5f, 0.0f, 0.0f }, glm::vec3{  0.0f,0.5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f})));

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile("obj/monkey.obj",
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);

    if (!scene)
    {
        std::cerr << "Não foi possível importar o arquivo" << std::endl;
    }

    std::srand(std::time(nullptr));

    auto mesh = scene->mMeshes[0];

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        auto face = mesh->mFaces[i];

        auto v1 = mesh->mVertices[face.mIndices[0]];
        auto v2 = mesh->mVertices[face.mIndices[1]];
        auto v3 = mesh->mVertices[face.mIndices[2]];

        primitives_.push_back(Primitive::PrimitiveUniquePtr(new Triangle(glm::vec3{v1.x, v1.y, v1.z},
                                                                         glm::vec3{v2.x, v2.y, v2.z}, glm::vec3{v3.x, v3.y, v3.z},
                                                                         glm::vec3{static_cast<float>(std::rand() % 256) / 255.0f, static_cast<float>(std::rand() % 256) / 255.0f, static_cast<float>(std::rand() % 256) / 255.0f})));
    }
}
