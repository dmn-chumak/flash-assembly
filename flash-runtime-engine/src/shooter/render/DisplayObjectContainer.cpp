#include <shooter/render/DisplayObjectContainer.h>
#include <shooter/render/GpuRenderer.h>

namespace shooter::render {
    DisplayObjectContainer::DisplayObjectContainer() {
        _children = nullptr;
    }

    DisplayObjectContainer *DisplayObjectContainer::DisplayObjectContainerConstruct() {
        DisplayObject::DisplayObjectConstruct();
        _children = new Array<DisplayObject>();
        return this;
    }

    void DisplayObjectContainer::render(IRender *renderer__) {
        Pointer<GpuRenderer> renderer = (GpuRenderer *)renderer__;

        sInt i = 0;
        if (_children->length() != sInt(0)) {
            renderer->attachState((DisplayObject *)this);
            for (i = sInt(0); i < _children->length(); i++) {
                _children->obtainAt((uInt)i)->render(renderer__);
            }
            renderer->detachState((DisplayObject *)this);
        }
    }

    void DisplayObjectContainer::update(double delta) {
        sInt i = 0;
        for (i = sInt(0); i < _children->length(); i++) {
            _children->obtainAt((uInt)i)->update(delta);
        }
    }

    void DisplayObjectContainer::appendChild(Pointer<DisplayObject> object) {
        if (object != nullptr && object->parentGetter() == nullptr) {
            _children->insertAt(_children->length(), object);
            object->parentSetter(this);
        }
    }

    void DisplayObjectContainer::removeChild(Pointer<DisplayObject> object) {
        if (object != nullptr && object->parentGetter().object() == this) {
            _children->removeAt((uInt)_children->indexOf(object));
            object->parentSetter(nullptr);
        }
    }

    void DisplayObjectContainer::removeAllChildren() {
        sInt i = 0;
        for (i = sInt(0); i < _children->length(); i++) {
            _children->obtainAt((uInt)i)->parentSetter(nullptr);
        }
        _children->length(0);
    }

    DisplayObjectContainer::~DisplayObjectContainer() {
    }
}

