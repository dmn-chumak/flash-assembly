#ifndef SHOOTER_RENDER_ANIMATION_SKELETON_H
#define SHOOTER_RENDER_ANIMATION_SKELETON_H

#include <flash/core/Core.h>
#include <shooter/render/animation/SkeletonPart.h>

namespace shooter::render::animation {
    class Skeleton : public Object {
        private:
        protected:
        public:
            Pointer<Array<SkeletonPart>> parts;
            Skeleton();
            Skeleton *SkeletonConstruct();
            virtual ~Skeleton() override;
    };
}

#endif

