#ifndef SHOOTER_RENDER_DISPLAY_OBJECT_REGION_H
#define SHOOTER_RENDER_DISPLAY_OBJECT_REGION_H

#include <shooter/render/common/GpuTextureRegion.h>
#include <flash/core/Core.h>
#include <shooter/render/DisplayObject.h>

using shooter::render::common::GpuTextureRegion;

namespace shooter::render {
    class DisplayObjectRegion : public DisplayObject {
        private:
            Pointer<GpuTextureRegion> _region;
        protected:
        public:
            DisplayObjectRegion();
            DisplayObjectRegion *DisplayObjectRegionConstruct(Pointer<GpuTextureRegion> region = nullptr);
            void render(IRender *renderer__) override;
            Pointer<GpuTextureRegion> regionGetter();
            void regionSetter(Pointer<GpuTextureRegion> value);
            virtual ~DisplayObjectRegion() override;
    };
}

#endif

