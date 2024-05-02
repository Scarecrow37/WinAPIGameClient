#pragma once

struct Rectangle
{
    float left;
    float top;
    float right;
    float bottom;

    float GetWidth() const;
    float GetHeight() const;
};
