#ifndef SHOOTER_RENDER_ANIMATION_SKELETON_PART_H
#define SHOOTER_RENDER_ANIMATION_SKELETON_PART_H

#include <flash/core/Core.h>

namespace shooter::render::animation {
    class SkeletonPart : public Object {
        private:
        protected:
        public:
            String texture;
            String name;
            SkeletonPart();
            SkeletonPart *SkeletonPartConstruct();
            virtual ~SkeletonPart() override;
    };
}

#endif

