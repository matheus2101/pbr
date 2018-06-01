#ifndef INTERSECTION_RECORD_H_
#define INTERSECTION_RECORD_H_

#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include "ray.h"
#include "PRNG.h"
#include "onb.h"
#include "material.h"
#include <omp.h>

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
    Type type_;

    Ray get_new_ray()
    {
        float r1 = prng.get_rand(omp_get_thread_num());
        float r2 = prng.get_rand(omp_get_thread_num());

        float theta = glm::acos(1 - r1);
        float phi = 2.0f * ((float)M_PI) * r2;

        glm::vec3 direction;
        direction.x = sin(theta) * cos(phi);
        direction.y = sin(theta) * sin(phi);
        direction.z = cos(theta);

        ONB onb;
        onb.setFromV(this->normal_);

        Ray new_ray;
        new_ray.origin_ = this->position_ + (this->normal_ * 0.001f);
        new_ray.direction_ = onb.getBasisMatrix() * direction;

        return new_ray;
    }

    Ray get_reflection(Ray& ray)
    {
        ONB onb_;

        onb_.setFromV(this->normal_);

        Ray newray;

        glm::vec3 newdir = glm::transpose(onb_.getBasisMatrix()) * ray.direction_;
        newdir = {newdir.x, -newdir.y, newdir.z};
        newray = {this->position_ + (this->normal_ * 0.001f), onb_.getBasisMatrix() * newdir};

        return newray;
    }
};

#endif /* INTERSECTION_RECORD_H_ */
