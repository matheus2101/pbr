#include "triangle.h"
#define EPSILON 0.000001

Triangle::Triangle(const glm::vec3 v0, const glm::vec3 v1,
 const glm::vec3 v2) : v0_{v0}, v1_{v1}, v2_{v2}
 {}

bool Triangle::intersect( const Ray &ray,
                    IntersectionRecord &intersection_record ) const
{
    glm::vec3 edge1, edge2, tvec, pvec, qvec;
    double det, t, u, v;

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
    if (u < 0.0 || u > det) return false;

    /* prepare to test V parameter */
    qvec = glm::cross(tvec,edge1);

    /* calculate V parameter and test bounds */
    v = glm::dot(ray.direction_, qvec);
    if (v < 0.0 || u + v > det) return false;

    /* calculate t, scale parameters, ray intersects triangle */
    t = glm::dot(edge2, qvec);
    t *= 1.0 / det;
    u *= 1.0 / det;
    v *= 1.0 / det;

    /* set the intersection record */
    intersection_record.position_ = glm::vec3{t, u, v};
    intersection_record.normal_ = glm::normalize(glm::cross(v2_ - v0_, v1_ - v0_));
    intersection_record.t_ = (intersection_record.position_ - ray.origin_)[0] / (ray.direction_ - ray.origin_)[0];

    return true;
}