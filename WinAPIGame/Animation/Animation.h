#pragma once
#include "Frame.h"
#include "../Containers/Vector.h"

struct Region;

class Animation
{
public:
    class Builder;

    void AddFrame(const Frame& frame);
    const Frame& GetFrame(size_t index) const;
    size_t GetFrameCount() const;

private:
    Animation();
    Dosuha::Vector<Frame> _frames;
    bool _loop;

public:
    class Builder
    {
    public:
        static Builder& GetInstance();
        Animation* Build() ;
        Builder& Initialize();
        Builder& AddFrame(const Frame& frame);
        Builder& AddFrame();
        Builder& AddFrame(Region region);
        Builder& AddFrame(Region region, std::function<void()> notifyEvent);
        Builder& AddFrame(Region region, float interval);
        Builder& AddFrame(Region region, float interval, std::function<void()> notifyEvent);
        Builder& NotLoop();

    private:
        Builder();
        Animation* _animation;
        Frame _frame;
    };
};
