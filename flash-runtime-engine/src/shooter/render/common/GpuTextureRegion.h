#ifndef SHOOTER_RENDER_COMMON_GPU_TEXTURE_REGION_H
#define SHOOTER_RENDER_COMMON_GPU_TEXTURE_REGION_H

namespace shooter::render::common {
    class GpuTextureRegion;
}

#include <flash/geometry/Rectangle.h>
#include <flash/core/Core.h>
#include <shooter/render/common/GpuTexture.h>

using flash::geometry::Rectangle;

namespace shooter::render::common {
    class GpuTextureRegion : public Object {
        private:
            Pointer<Vector<double>> _vertex;
            Pointer<GpuTexture> _parent;
        protected:
        public:
            GpuTextureRegion();
            GpuTextureRegion *GpuTextureRegionConstruct(Pointer<GpuTexture> parent, Pointer<Rectangle> bounds);
            Pointer<Vector<double>> vertexGetter();
            Pointer<GpuTexture> parentGetter();
            virtual ~GpuTextureRegion() override;
    };
}

#endif

