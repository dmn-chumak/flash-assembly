#include <shooter/render/animation/SkeletonPart.h>

namespace shooter::render::animation {
    SkeletonPart::SkeletonPart() {
        texture = nullptr;
        name = nullptr;
    }

    SkeletonPart *SkeletonPart::SkeletonPartConstruct() {
        return this;
    }

    SkeletonPart::~SkeletonPart() {
    }
}

