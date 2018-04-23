#include "primitive.h"

Primitive::Primitive( void )
{}

Primitive::Primitive (const glm::vec3 color,const glm::vec3 brdf, const glm::vec3 emittance):
    color_{color},
    brdf_{brdf},
    emittance_{emittance}
{}

Primitive::~Primitive( void )
{}

void Primitive::setColor( const glm::vec3 color )
{
    color_ = color;
}
