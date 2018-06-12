#include "main.h"
#include "PRNG.h"
#include <omp.h>

PRNG prng;

int main(void)
{
    unsigned int x_resolution = 1280;
    unsigned int y_resolution = 720;

    PinholeCamera camera{
        -3.2f,
        3.2f,
        -1.8f,
        1.8f,
        2.5f,
        glm::ivec2{x_resolution, y_resolution},
        glm::vec3{-0.70f, 2.8f, 3.25f},  // position
        glm::vec3{0.0f, 1.0f, 0.0f},     // up
        glm::vec3{-0.70f, 0.3f, -3.0f}}; // look at
    Scene scene{};

    // scene.load();
    scene.loadFinalScene();
    scene.buildBVH();

    prng = PRNG();

    Buffer rendering_buffer{x_resolution, y_resolution};
    glm::vec3 background_color{0.0f, 0.0f, 0.0f};

    // Set up the renderer.
    RayTracer rt(camera,
                 scene,
                 background_color,
                 rendering_buffer);

    rt.integrate(); // Renders the final image.

    // Save the rendered image to a .ppm file.
    rendering_buffer.save("output_image.ppm");

    return EXIT_SUCCESS;
}
