#include "Animation.h"

#include <utility>

void Animation::AddFrame(const Frame& frame)
{
    _frames.PushBack(frame);
}

const Frame& Animation::GetFrame(size_t index) const
{
    const size_t frameSize = _frames.Size();
    while (index >= frameSize) 
    {
        if (_loop) index -= frameSize; 
        else index = frameSize - 1;
    }
    return _frames[index];
}

size_t Animation::GetFrameCount() const
{
    return _frames.Size();
}

Animation::Animation(): _loop(true)
{
}

Animation::Builder& Animation::Builder::GetInstance()
{
    static Builder builder;
    return builder;
}

Animation* Animation::Builder::Build()
{
    Animation* result = _animation;
    _animation = nullptr;
    return result;
}

Animation::Builder& Animation::Builder::Initialize()
{
    _animation = new Animation();
    _frame = {};
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame(const Frame& frame)
{
    _frame = frame;
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame()
{
    _frame.region = Region{
        _frame.region.x + _frame.region.width, _frame.region.y, _frame.region.width, _frame.region.height
    };
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame(const Region region)
{
    _frame.region = region;
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame(const Region region, std::function<void()> notifyEvent)
{
    _frame.region = region;
    _frame.onStart = std::move(notifyEvent);
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame(const Region region, const float interval)
{
    _frame.region = region;
    _frame.interval = interval;
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::AddFrame(const Region region, const float interval,
                                                 std::function<void()> notifyEvent)
{
    _frame.region = region;
    _frame.interval = interval;
    _frame.onStart = std::move(notifyEvent);
    _animation->AddFrame(_frame);
    return *this;
}

Animation::Builder& Animation::Builder::NotLoop()
{
    _animation->_loop = false;
    return *this;
}

Animation::Builder::Builder() : _animation(nullptr), _frame({})
{
}
