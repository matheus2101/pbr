#include "primitive.h"

Primitive::Primitive( void )
{}

Primitive::Primitive (const glm::vec3 color):
    color_{color}
{}

Primitive::~Primitive( void )
{}

void Primitive::setColor( const glm::vec3 color )
{
    color_ = color;
}
