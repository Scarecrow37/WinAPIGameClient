#pragma once

struct Vector
{
    static const Vector Zero;
    static const Vector Up;
    static const Vector Down;

    float x;
    float y;

    Vector operator+(const Vector& rhs) const;
    Vector& operator+=(const Vector& rhs);
    Vector operator*(float scalar) const;
    bool operator==(const Vector& rhs) const;

    float SquareMagnitude() const;
    Vector operator-(const Vector& rhs) const;
    Vector operator/(float scalar) const;
};
