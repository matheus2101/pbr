#include "triangle.h"
#define EPSILON 0.000001f

Triangle::Triangle(const glm::vec3 v0, const glm::vec3 v1,
 const glm::vec3 v2, const glm::vec3 color, const glm::vec3 brdf, const glm::vec3 emittance): 
Primitive::Primitive{color, brdf, emittance}, v0_{v0}, v1_{v1}, v2_{v2} {}

bool Triangle::intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const
{
    glm::vec3 edge1, edge2, tvec, pvec, qvec;
    float det, inv_det, t, u, v;

    /* find vectors for two edges sharing vert0*/
    edge1 = v1_ - v0_;
    edge2 = v2_ - v0_;

    /* begin to calculating determinant */
    pvec = glm::cross(ray.direction_, edge2);

    /* if determinant is near zero, ray lies in plane of triangle */
    det = glm::dot(edge1, pvec);

    /* test for culling */
    if (det < EPSILON) return false;

    /* calculate distance form vert0 to ray origin */
    tvec = ray.origin_ - v0_;

    /* calculate U parameter and test bounds */
    u = glm::dot(tvec, pvec);
    if ((u < 0.0f) || (u > det)) return false;

    /* prepare to test V parameter */
    qvec = glm::cross(tvec,edge1);

    /* calculate V parameter and test bounds */
    v = glm::dot(ray.direction_, qvec);
    if ((v < 0.0f) || ((u + v) > det)) return false;

    /* calculate t, scale parameters, ray intersects triangle */
    t = glm::dot(edge2, qvec);
    inv_det = 1.0f / det;
    t *= inv_det;
    u *= inv_det;
    v *= inv_det;

    intersection_record.brdf_ = brdf_ / ((float) M_PI);
    intersection_record.emittance_ = emittance_;
    intersection_record.normal_ = glm::normalize(glm::cross(v2_ - v0_, v1_ - v0_));
    intersection_record.color_ = color_;
    intersection_record.t_ = t;
    intersection_record.position_ = ray.origin_ + ray.direction_ * t;


    return true;
}

AABB Triangle::getAABB(void) const
{
    AABB aabb;

    aabb.min_ = glm::min(glm::min(v0_, v1_), v2_);
    aabb.max_ = glm::max(glm::max(v0_, v1_), v2_);
    aabb.centroid_ = (1.0f / 3.0f) * (v0_ + v1_ + v1_);
    return aabb;
}