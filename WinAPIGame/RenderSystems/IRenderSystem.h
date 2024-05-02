#pragma once
#include "IDraw.h"
#include "../Interfaces/IFinalize.h"
#include "../Interfaces/IInitialize.h"

class IRenderer;

class IRenderSystem : public IInitialize, public IFinalize, public IDraw
{
public:
    virtual void SetRenderer(IRenderer* renderer) = 0;
    virtual IRenderer* GetRenderer() const = 0;
};
