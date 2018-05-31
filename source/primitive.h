#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include <memory>

#include "aabb.h"
#include "ray.h"
#include "intersection_record.h"

class Primitive
{
public:

    typedef std::unique_ptr< Primitive > PrimitiveUniquePtr;

    Primitive( void );

    Primitive( glm::vec3 color, glm::vec3 brdf, glm::vec3 emittance );

    void setColor( glm::vec3 color );

    virtual ~Primitive( void );

    virtual bool intersect( const Ray &ray,
                            IntersectionRecord &intersection_record ) const = 0;

    virtual AABB getAABB(void) const = 0;

    glm::vec3 color_;
    glm::vec3 brdf_;
    glm::vec3 emittance_;
};

#endif /* PRIMITIVE_H_ */

