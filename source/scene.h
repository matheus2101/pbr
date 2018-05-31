#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include "primitive.h"
#include "sphere.h" 
#include "triangle.h"
#include "bvh.h"

class Scene
{
public:

    Scene( void );

    ~Scene( void );

    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    void load( void );
    void buildBVH(void);

    std::vector< Primitive::PrimitiveUniquePtr > primitives_;
    const BVH *bvh_ = nullptr;
};

#endif /* SCENE_H_ */

