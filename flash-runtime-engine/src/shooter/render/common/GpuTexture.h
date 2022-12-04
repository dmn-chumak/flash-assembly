#ifndef SHOOTER_RENDER_COMMON_GPU_TEXTURE_H
#define SHOOTER_RENDER_COMMON_GPU_TEXTURE_H

namespace shooter::render::common {
    class GpuTexture;
}

#include <flash/display/BitmapData.h>
#include <flash/display3D/Context3D.h>
#include <flash/display3D/Context3DTextureFormat.h>
#include <flash/display3D/Texture3D.h>
#include <flash/geometry/Rectangle.h>
#include <flash/utils/ByteArray.h>
#include <flash/core/Core.h>
#include <shooter/render/common/GpuTextureRegion.h>
#include <shooter/utils/MathUtils.h>

using flash::display::BitmapData;
using flash::display3D::Context3D;
using flash::display3D::Context3DTextureFormat;
using flash::display3D::Texture3D;
using flash::geometry::Rectangle;
using flash::utils::ByteArray;
using shooter::utils::MathUtils;

namespace shooter::render::common {
    class GpuTexture : public Object {
        private:
            Pointer<Vector<String>> _regionsName;
            Pointer<Array<GpuTextureRegion>> _regionsList;
            Pointer<GpuTextureRegion> _region;
            Pointer<Texture3D> _parent;
            Pointer<BitmapData> _bitmap;
            double _width;
            double _height;
        protected:
        public:
            GpuTexture();
            GpuTexture *GpuTextureConstruct(Pointer<Context3D> context3D, Pointer<BitmapData> bitmap, Pointer<ByteArray> regions = nullptr);
            Pointer<GpuTextureRegion> obtainRegion(String name = nullptr);
            Pointer<Texture3D> parentGetter();
            double widthGetter();
            double heightGetter();
            virtual ~GpuTexture() override;
    };
}

#endif

