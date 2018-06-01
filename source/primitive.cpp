#include "primitive.h"

Primitive::Primitive( void )
{}

Primitive::Primitive (const glm::vec3 color,const glm::vec3 brdf, const glm::vec3 emittance, Type type):
    color_{color},
    brdf_{brdf},
    emittance_{emittance},
    type_{type}
{}

Primitive::~Primitive( void )
{}

void Primitive::setColor( const glm::vec3 color )
{
    color_ = color;
}
