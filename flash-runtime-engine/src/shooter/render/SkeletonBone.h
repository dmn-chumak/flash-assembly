#ifndef SHOOTER_RENDER_SKELETON_BONE_H
#define SHOOTER_RENDER_SKELETON_BONE_H

#include <flash/geometry/Matrix.h>
#include <flash/core/Core.h>
#include <shooter/render/DisplayObjectRegion.h>

using flash::geometry::Matrix;

namespace shooter::render {
    class SkeletonBone : public DisplayObjectRegion {
        private:
        protected:
        public:
            SkeletonBone();
            SkeletonBone *SkeletonBoneConstruct();
            void matrixSetter(Pointer<Matrix> value);
            virtual ~SkeletonBone() override;
    };
}

#endif

