#pragma once
#include "../IDraw.h"
#include "../../Interfaces/IFinalize.h"
#include "../../Interfaces/IInitialize.h"

class IRenderer : public IInitialize, public IFinalize, public IDraw
{
public:
    virtual void BeginDraw() = 0;
    virtual void EndDraw() = 0;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
};
