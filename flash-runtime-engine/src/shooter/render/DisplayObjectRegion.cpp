#include <shooter/render/DisplayObjectRegion.h>
#include <shooter/render/GpuRenderer.h>

namespace shooter::render {
    DisplayObjectRegion::DisplayObjectRegion() {
        _region = nullptr;
    }

    DisplayObjectRegion *DisplayObjectRegion::DisplayObjectRegionConstruct(Pointer<GpuTextureRegion> region) {
        DisplayObject::DisplayObjectConstruct();
        _region = region;
        return this;
    }

    void DisplayObjectRegion::render(IRender *renderer__) {
        Pointer<GpuRenderer> renderer = (GpuRenderer *)renderer__;

        if (_region != nullptr) {
            renderer->attachState(this);
            renderer->renderTextureRegion(_region);
            renderer->detachState(this);
        }
    }

    Pointer<GpuTextureRegion> DisplayObjectRegion::regionGetter() {
        return _region;
    }

    void DisplayObjectRegion::regionSetter(Pointer<GpuTextureRegion> value) {
        _region = value;
    }

    DisplayObjectRegion::~DisplayObjectRegion() {
    }
}

