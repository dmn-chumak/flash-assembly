#ifndef SHOOTER_RENDER_ANIMATION_ANIMATION_H
#define SHOOTER_RENDER_ANIMATION_ANIMATION_H

#include <flash/core/Core.h>
#include <shooter/render/animation/AnimationFrame.h>

namespace shooter::render::animation {
    class Animation : public Object {
        private:
        protected:
        public:
            Pointer<Array<AnimationFrame>> frames;
            Animation();
            Animation *AnimationConstruct();
            virtual ~Animation() override;
    };
}

#endif

