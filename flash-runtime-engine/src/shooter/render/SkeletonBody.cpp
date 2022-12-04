#include <shooter/render/SkeletonBody.h>
#include <shooter/render/animation/AnimationState.h>

using shooter::render::animation::AnimationState;

namespace shooter::render {
    const double SkeletonBody::FRAME_RATE = Double(16.5);

    void SkeletonBody::validateBonesTree() {
        Pointer<Array<AnimationState>> states = nullptr;
        sInt i = 0;
        sInt index = 0;
        Pointer<SkeletonBone> bone = nullptr;
        removeAllChildren();
        if (_animation != nullptr) {
            states = _animation->frames->obtainAt((uInt)_currentFrame)->states;
            for (i = sInt(0); i < states->length(); i++) {
                index = _namesList->indexOf(states->obtainAt((uInt)i)->name);
                if (index != -sInt(1)) {
                    bone = _bonesList->obtainAt((uInt)index);
                    bone->matrixSetter(states->obtainAt((uInt)i)->matrix);
                    appendChild(bone);
                }
            }
        }
    }

    SkeletonBody::SkeletonBody() {
        _bonesList = nullptr;
        _namesList = nullptr;
        _currentFrame = 0;
        _totalFrames = 0;
        _isPlayingOnce = false;
        _isPlaying = false;
        _animation = nullptr;
    }

    SkeletonBody *SkeletonBody::SkeletonBodyConstruct() {
        DisplayObjectContainer::DisplayObjectContainerConstruct();
        _bonesList = new Array<SkeletonBone>();
        _namesList = new Vector<String>();
        _currentFrame = sInt(0);
        _totalFrames = sInt(0);
        _isPlayingOnce = false;
        _isPlaying = false;
        _animation = nullptr;
        return this;
    }

    void SkeletonBody::update(double delta) {
        if (_animation != nullptr && _isPlaying) {
            if (++_currentFrame == _totalFrames) {
                if (_isPlayingOnce) {
                    stop();
                }
                _currentFrame = sInt(0);
            }
            validateBonesTree();
        }
    }

    void SkeletonBody::appendBone(String name, Pointer<SkeletonBone> bone) {
        sInt index = 0;
        index = _namesList->length();
        if (index != -sInt(1)) {
            _bonesList->insertAt((uInt)index, bone);
            _namesList->insertAt((uInt)index, name);
            validateBonesTree();
        }
    }

    void SkeletonBody::removeBone(String name) {
        sInt index = 0;
        index = _namesList->indexOf(name);
        if (index != -sInt(1)) {
            _bonesList->removeAt((uInt)index);
            _namesList->removeAt((uInt)index);
            validateBonesTree();
        }
    }

    void SkeletonBody::play(bool once) {
        _isPlayingOnce = once;
        _isPlaying = true;
    }

    void SkeletonBody::stop() {
        _isPlayingOnce = false;
        _isPlaying = false;
    }

    Pointer<Animation> SkeletonBody::animationGetter() {
        return _animation;
    }

    void SkeletonBody::animationSetter(Pointer<Animation> value) {
        _animation = value;
        _currentFrame = sInt(0);
        _isPlayingOnce = false;
        _isPlaying = false;
        if (_animation != nullptr) {
            _totalFrames = _animation->frames->length();
        } else {
            _totalFrames = sInt(0);
        }
        validateBonesTree();
    }

    SkeletonBody::~SkeletonBody() {
    }
}

