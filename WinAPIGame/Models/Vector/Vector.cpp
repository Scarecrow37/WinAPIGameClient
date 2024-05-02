#include "Vector.h"

const Vector Vector::Zero{0, 0};
const Vector Vector::Up{0, 1};
const Vector Vector::Down{0, -1};

Vector Vector::operator+(const Vector& rhs) const
{
    return {x + rhs.x, y + rhs.y};
}

Vector& Vector::operator+=(const Vector& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vector Vector::operator*(const float scalar) const
{
    return {x * scalar, y * scalar};
}

bool Vector::operator==(const Vector& rhs) const
{
    return static_cast<long long>(x * 1000000) == static_cast<long long>(rhs.x * 1000000) &&
        static_cast<long long>(y * 1000000) == static_cast<long long>(rhs.y * 1000000);
}

float Vector::SquareMagnitude() const
{
    return x * x + y * y;
}

Vector Vector::operator-(const Vector& rhs) const
{
    return {x - rhs.x, y - rhs.y};
}

Vector Vector::operator/(float scalar) const
{
    return {x / scalar, y / scalar};
}
