#include "Rectangle.h"

float Rectangle::GetWidth() const
{
    return left + right;
}

float Rectangle::GetHeight() const
{
    return top + bottom;
}

