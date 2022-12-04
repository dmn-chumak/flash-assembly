#ifndef SHOOTER_RENDER_BUILDER_ANIMATION_BUILDER_H
#define SHOOTER_RENDER_BUILDER_ANIMATION_BUILDER_H

#include <flash/utils/ByteArray.h>
#include <shooter/render/animation/Animation.h>
#include <shooter/render/animation/AnimationFrame.h>
#include <shooter/render/animation/AnimationState.h>
#include <flash/core/Core.h>

using flash::utils::ByteArray;
using shooter::render::animation::Animation;
using shooter::render::animation::AnimationFrame;
using shooter::render::animation::AnimationState;

namespace shooter::render::builder {
    class AnimationBuilder : public Object {
        public:
            static Pointer<Animation> create(Pointer<ByteArray> source);
    };
}

#endif

