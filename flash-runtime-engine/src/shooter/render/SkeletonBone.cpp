#include <shooter/render/SkeletonBone.h>

namespace shooter::render {
    SkeletonBone::SkeletonBone() {

    }

    SkeletonBone *SkeletonBone::SkeletonBoneConstruct() {
        DisplayObjectRegion::DisplayObjectRegionConstruct();
        return this;
    }

    void SkeletonBone::matrixSetter(Pointer<Matrix> value) {
        _isMatrixValid = true;
        _matrix = value;
    }

    SkeletonBone::~SkeletonBone() {
    }
}

