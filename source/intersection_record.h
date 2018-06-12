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
    float roughness_;

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

    Ray importance_sampling(glm::vec3 direction, float alpha)
    {
        float r1 = prng.get_rand(omp_get_thread_num());
        float r2 = prng.get_rand(omp_get_thread_num());

        float phi = 2 * (float)M_PI * r2;
        float theta = atan(sqrt(-(alpha * alpha) * log(1.0f - r1)));
        glm::vec3 m = glm::vec3{cos(phi) * sin(theta), cos(theta), sin(phi) * sin(theta)};

        ONB onb;
        onb.setFromV(this->normal_);

        glm::vec3 wo = -glm::normalize(glm::transpose(onb.getBasisMatrix()) * direction);

        // generate the light ray by reflecting wo about m
        glm::vec3 wi = 2.0f * m * dot(m, wo) - wo;

        Ray new_ray;

        new_ray.origin_ = this->position_ + (this->normal_ * 0.001f);
        new_ray.direction_ = glm::normalize(onb.getBasisMatrix() * wi);

        return new_ray;
    }

    Ray get_reflection(Ray &ray)
    {
        ONB onb_;

        onb_.setFromV(this->normal_);

        Ray newray;

        glm::vec3 newdir = glm::transpose(onb_.getBasisMatrix()) * ray.direction_;
        newdir = {newdir.x, -newdir.y, newdir.z};
        newray = {this->position_ + (this->normal_ * 0.001f), onb_.getBasisMatrix() * newdir};

        return newray;
    }

    Ray get_refraction(Ray &ray, float n1, float n2)
    {
        float n = n1 / n2;
        float cos1 = -glm::dot(this->normal_, ray.direction_);
        float cos2 = 1.0 - n * n * (1.0f - cos1 * cos1);

        cos2 = sqrt(cos2);
        glm::vec3 direction = n * ray.direction_ + (n * cos1 - cos2) * this->normal_;

        Ray new_ray;
        new_ray = {this->position_ + 0.001f * direction, direction};

        return new_ray;
    }
};

#endif /* INTERSECTION_RECORD_H_ */
