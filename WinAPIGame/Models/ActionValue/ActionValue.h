#pragma once
#include "../Vector/Vector.h"

union ActionValue
{
    struct
    {
        short _;
        bool on;
    };

    struct
    {
        float scalar;
    };

    Vector vector;

    operator bool() const;

    ActionValue& operator+=(const ActionValue& rhs);
};
