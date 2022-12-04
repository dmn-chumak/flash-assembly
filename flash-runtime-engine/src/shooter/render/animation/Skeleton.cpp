#include <shooter/render/animation/Skeleton.h>

namespace shooter::render::animation {
    Skeleton::Skeleton() {
        parts = nullptr;
    }

    Skeleton *Skeleton::SkeletonConstruct() {
        parts = new Array<SkeletonPart>();
        return this;
    }

    Skeleton::~Skeleton() {
    }
}

