#include <shooter/render/builder/SkeletonBuilder.h>

namespace shooter::render::builder {
    Pointer<Skeleton> SkeletonBuilder::create(Pointer<ByteArray> source) {
        Pointer<Skeleton> skeleton = nullptr;
        sInt partsCount = 0;
        sInt i = 0;
        Pointer<SkeletonPart> part = nullptr;
        skeleton = (new Skeleton())->SkeletonConstruct();
        partsCount = source->readInt();
        for (i = sInt(0); i < partsCount; i++) {
            part = (new SkeletonPart())->SkeletonPartConstruct();
            part->texture = source->readUTF();
            part->name = source->readUTF();
            skeleton->parts->insertLast(part);
        }
        return skeleton;
    }

}

