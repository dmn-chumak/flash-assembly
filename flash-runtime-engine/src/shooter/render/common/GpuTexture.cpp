#include <shooter/render/common/GpuTexture.h>
#include <flash/utils/Math.h>
#include <flash/runtime/Number.h>

using flash::utils::Math;
using namespace flash::runtime;

namespace shooter::render::common {
    GpuTexture::GpuTexture() {
        _regionsName = nullptr;
        _regionsList = nullptr;
        _region = nullptr;
        _parent = nullptr;
        _bitmap = nullptr;
        _width = 0;
        _height = 0;
    }

    GpuTexture *GpuTexture::GpuTextureConstruct(Pointer<Context3D> context3D, Pointer<BitmapData> bitmap, Pointer<ByteArray> regions) {
        sInt regionsCount = 0;
        sInt i = 0;
        Pointer<Rectangle> regionRect = nullptr;
        String regionName = nullptr;

        _width = bitmap->width();
        _height = bitmap->height();

        _parent = context3D->createTexture(bitmap->width(), bitmap->height());
        _parent->uploadFromBitmapData(bitmap);

        _bitmap = bitmap;
        _regionsList = new Array<GpuTextureRegion>();
        _regionsName = new Vector<String>();
        _region = (new GpuTextureRegion())->GpuTextureRegionConstruct(this, new Rectangle(Double(0), Double(0), bitmap->width(), bitmap->height()));
        if (regions == nullptr) {
            return this;
        }

        regionsCount = regions->readInt();

        for (i = sInt(0); i < regionsCount; i++) {
            regionRect = new Rectangle();
            regionName = regions->readUTF();
            regionRect->x = regions->readInt();
            regionRect->y = regions->readInt();
            regionRect->width = regions->readInt();
            regionRect->height = regions->readInt();
            _regionsList->insertLast((new GpuTextureRegion())->GpuTextureRegionConstruct(this, regionRect));
            _regionsName->insertLast(regionName);
        }
        return this;
    }

    Pointer<GpuTextureRegion> GpuTexture::obtainRegion(String name) {
        sInt index = 0;
        if (name == nullptr) {
            return _region;
        }
        index = _regionsName->indexOf(name);
        if (index != -sInt(1)) {
            return _regionsList->obtainAt((uInt)index);
        }
        return _region;
    }

    Pointer<Texture3D> GpuTexture::parentGetter() {
        return _parent;
    }

    double GpuTexture::widthGetter() {
        return _width;
    }

    double GpuTexture::heightGetter() {
        return _height;
    }

    GpuTexture::~GpuTexture() {
    }
}

