#include "pinhole_camera.h"

PinholeCamera::PinholeCamera( void )
{}

PinholeCamera::PinholeCamera( const float min_x,
                                        const float max_x,
                                        const float min_y,
                                        const float max_y,
                                        const float distance,
                                        const glm::ivec2 &resolution,
                                        const glm::vec3 &position,
                                        const glm::vec3 &up_vector,
                                        const glm::vec3 &look_at ) :
        Camera::Camera{ resolution, 
                        position,
                        up_vector,
                        look_at },
        min_x_{ min_x },
        max_x_{ max_x },
        min_y_{ min_y },
        max_y_{ max_y },
        distance_{distance}
{}

Ray PinholeCamera::getWorldSpaceRay( const glm::vec2 &pixel_coord ) const
{
    float width = max_x_ - min_x_;
    float height = max_y_ - min_y_;

    // glm::vec3 s{ min_x_ + (width * ((pixel_coord[0] + 0.5f) / resolution_[0])),
    //             (min_y_ + (height * ((pixel_coord[1] + 0.5f) / resolution_[1]))) * -1,
    //             -1.0f};

    // return Ray{ onb_.getBasisMatrix() * s + position_, glm::normalize( onb_.getBasisMatrix() * (s - position_ ))};

    glm::vec3 s{(pixel_coord[0] + 0.5f) / static_cast<float>(resolution_[0]) * width + min_x_,
                           (pixel_coord[1] + 0.5f) / static_cast<float>(resolution_[1]) * -height + max_y_,
                           -distance_};

    return Ray{position_, glm::normalize(onb_.getBasisMatrix() * s)};
}

