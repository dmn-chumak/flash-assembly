#ifndef SHOOTER_RENDER_SKELETON_BODY_H
#define SHOOTER_RENDER_SKELETON_BODY_H

#include <shooter/render/animation/Animation.h>
#include <flash/core/Core.h>
#include <shooter/render/DisplayObjectContainer.h>
#include <shooter/render/SkeletonBone.h>

using shooter::render::animation::Animation;

namespace shooter::render {
    class SkeletonBody : public DisplayObjectContainer {
        private:
        protected:
            static const double FRAME_RATE;
            Pointer<Array<SkeletonBone>> _bonesList;
            Pointer<Vector<String>> _namesList;
            sInt _currentFrame;
            sInt _totalFrames;
            bool _isPlayingOnce;
            bool _isPlaying;
            Pointer<Animation> _animation;
            void validateBonesTree();
        public:
            SkeletonBody();
            SkeletonBody *SkeletonBodyConstruct();
            void update(double delta) override;
            void appendBone(String name, Pointer<SkeletonBone> bone);
            void removeBone(String name);
            void play(bool once = false);
            void stop();
            Pointer<Animation> animationGetter();
            void animationSetter(Pointer<Animation> value);
            virtual ~SkeletonBody() override;
    };
}

#endif

