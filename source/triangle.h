#ifndef __TRIANGLE_H_
#define __TRIANGLE_H_

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include "primitive.h"
#include "intersection_record.h"
#include "ray.h"

class Triangle : public Primitive 
{
public:
    Triangle( void) = delete;
    Triangle( const glm::vec3 v1, const glm::vec3 v2,
     const glm::vec3 v3);
    bool intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const;

    glm::vec3 v0_, v1_, v2_;
};

#endif