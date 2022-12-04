#ifndef SHOOTER_RENDER_ANIMATION_ANIMATION_FRAME_H
#define SHOOTER_RENDER_ANIMATION_ANIMATION_FRAME_H

#include <flash/core/Core.h>
#include <shooter/render/animation/AnimationState.h>

namespace shooter::render::animation {
    class AnimationFrame : public Object {
        private:
        protected:
        public:
            Pointer<Array<AnimationState>> states;
            AnimationFrame();
            AnimationFrame *AnimationFrameConstruct();
            virtual ~AnimationFrame() override;
    };
}

#endif

