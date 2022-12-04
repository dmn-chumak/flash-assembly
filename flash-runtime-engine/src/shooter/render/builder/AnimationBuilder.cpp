#include <shooter/render/builder/AnimationBuilder.h>

namespace shooter::render::builder {
    Pointer<Animation> AnimationBuilder::create(Pointer<ByteArray> source) {
        Pointer<Animation> animation = nullptr;
        sInt framesCount = 0;
        sInt i = 0;
        Pointer<AnimationFrame> frame = nullptr;
        sInt statesCount = 0;
        sInt j = 0;
        Pointer<AnimationState> state = nullptr;
        animation = (new Animation())->AnimationConstruct();
        framesCount = source->readInt();
        for (i = sInt(0); i < framesCount; i++) {
            frame = (new AnimationFrame())->AnimationFrameConstruct();
            statesCount = source->readInt();
            for (j = sInt(0); j < statesCount; j++) {
                state = (new AnimationState())->AnimationStateConstruct();
                state->name = source->readUTF();
                state->matrix->tx = (float)source->readDouble();
                state->matrix->ty = (float)source->readDouble();
                state->matrix->a = (float)source->readDouble();
                state->matrix->b = (float)source->readDouble();
                state->matrix->c = (float)source->readDouble();
                state->matrix->d = (float)source->readDouble();
                frame->states->insertLast(state);
            }
            animation->frames->insertLast(frame);
        }
        return animation;
    }

}

