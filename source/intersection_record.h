#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "ray.h"
#include "PRNG.h"
#include "onb.h"

#define _USE_MATH_DEFINES

extern PRNG prng;

struct IntersectionRecord
{
    float t_;
    glm::vec3 position_;
    glm::vec3 normal_;
    glm::vec3 color_;
    glm::vec3 brdf_;
    glm::vec3 emittance_;

    Ray get_new_ray()
    {
        float r1 = prng.get_rand(0);
        float r2 = prng.get_rand(0);

        float theta = std::acos(1 - r1);
        float phi = 2 * M_PI * r2;

        glm::vec3 direction;
        direction.x = sinf(theta) * cosf(phi);
        direction.y = sinf(theta) * sinf(phi);
        direction.z = cosf(theta);

        ONB onb;
        onb.setFromV(this->normal_);

        Ray new_ray;
        new_ray.origin_ = this->position_;
        new_ray.direction_ = onb.getBasisMatrix() * direction;
        

        return new_ray;
    }
};

#endif /* INTERSECTION_RECORD_H_ */
