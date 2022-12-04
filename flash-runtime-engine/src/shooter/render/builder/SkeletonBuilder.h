#ifndef SHOOTER_RENDER_BUILDER_SKELETON_BUILDER_H
#define SHOOTER_RENDER_BUILDER_SKELETON_BUILDER_H

#include <flash/utils/ByteArray.h>
#include <shooter/render/animation/Skeleton.h>
#include <shooter/render/animation/SkeletonPart.h>
#include <flash/core/Core.h>

using flash::utils::ByteArray;
using shooter::render::animation::Skeleton;
using shooter::render::animation::SkeletonPart;

namespace shooter::render::builder {
    class SkeletonBuilder : public Object {
        public:
            static Pointer<Skeleton> create(Pointer<ByteArray> source);
    };
}

#endif

