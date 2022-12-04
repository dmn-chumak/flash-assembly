#include <shooter/render/animation/AnimationState.h>

namespace shooter::render::animation {
    AnimationState::AnimationState() {
        matrix = nullptr;
        name = nullptr;
    }

    AnimationState *AnimationState::AnimationStateConstruct() {
        matrix = new Matrix();
        return this;
    }

    AnimationState::~AnimationState() {
    }
}

