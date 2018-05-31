#include "sphere.h"

Sphere::Sphere( void )
{}

Sphere::Sphere( const glm::vec3 &center,
                const glm::vec3 color, const glm::vec3 brdf,
                const glm::vec3 emittance, float radius ) :
        center_{ center },
        Primitive::Primitive{color, brdf, emittance},
        radius_( radius )   
{}

bool Sphere::intersect( const Ray &ray,
                        IntersectionRecord &intersection_record ) const
{
    /* Ray-sphere intersection test adapted from the very efficient algorithm presented in the article:
     *
     *     "Intersection of a Ray with a Sphere".
     *     Jeff Hultquist.
     *     Graphics Gems.
     *     Academic Press.
     *     1990.
     */

    float t1;
    float t2;

    glm::vec3 eo = center_ - ray.origin_;
    float v = glm::dot( eo, ray.direction_ );
    float disc = ( radius_ * radius_ ) - ( glm::dot( eo, eo ) - ( v * v ) );

    if ( disc < 0.0f )
        return false;                           // no intersection
    else
    {
        float d = sqrt( disc );
        t1 = v - d;                             // first intersection point
        t2 = v + d;                             // second intersection point
    }

    // Set the intersection record
    intersection_record.brdf_ = brdf_ / ((float) M_PI);
    intersection_record.emittance_ = emittance_;
    intersection_record.t_ =  ( t1 > 0.00001f ) ? t1 : t2;
    intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;
    intersection_record.normal_ = glm::normalize( intersection_record.position_ - center_ );
    intersection_record.color_ = color_;

    return true;
}

AABB Sphere::getAABB(void) const
{
    AABB aabb;

    aabb.min_ = center_ - radius_;
    aabb.max_ = center_ + radius_;
    aabb.centroid_ = center_;
    return aabb;
}