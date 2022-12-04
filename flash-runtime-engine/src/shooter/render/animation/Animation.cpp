#include <shooter/render/animation/Animation.h>

namespace shooter::render::animation {
    Animation::Animation() {
        frames = nullptr;
    }

    Animation *Animation::AnimationConstruct() {
        frames = new Array<AnimationFrame>();
        return this;
    }

    Animation::~Animation() {
    }
}

