#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <sstream>
#include <iomanip>
#include <cmath>

#include "camera.h"
#include "scene.h"
#include "buffer.h"

class RayTracer
{
public:

    RayTracer( Camera &camera,
               const Scene &scene,
               const glm::vec3 background_color,
               Buffer &buffer );

    void integrate( void );
    glm::vec3 L(Ray &ray, unsigned depth);
    Ray get_new_ray(IntersectionRecord intersection_record);
    glm::vec3 cook_torrance(glm::vec3 wi, glm::vec3 wo, IntersectionRecord intersection_record);
    float schlick(glm::vec3 incident, glm::vec3 normal, float n1, float n2);
    private :

        const Camera &camera_;

    const Scene &scene_;

    glm::dvec3 background_color_;

    Buffer &buffer_;

};

#endif /* RAYTRACER_H_ */

