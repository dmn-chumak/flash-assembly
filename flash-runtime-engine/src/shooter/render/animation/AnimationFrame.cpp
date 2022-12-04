#include <shooter/render/animation/AnimationFrame.h>

namespace shooter::render::animation {
    AnimationFrame::AnimationFrame() {
        states = nullptr;
    }

    AnimationFrame *AnimationFrame::AnimationFrameConstruct() {
        states = new Array<AnimationState>();
        return this;
    }

    AnimationFrame::~AnimationFrame() {
    }
}

