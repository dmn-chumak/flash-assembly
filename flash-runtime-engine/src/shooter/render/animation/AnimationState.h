#ifndef SHOOTER_RENDER_ANIMATION_ANIMATION_STATE_H
#define SHOOTER_RENDER_ANIMATION_ANIMATION_STATE_H

#include <flash/geometry/Matrix.h>
#include <flash/core/Core.h>

using flash::geometry::Matrix;

namespace shooter::render::animation {
    class AnimationState : public Object {
        private:
        protected:
        public:
            Pointer<Matrix> matrix;
            String name;
            AnimationState();
            AnimationState *AnimationStateConstruct();
            virtual ~AnimationState() override;
    };
}

#endif

