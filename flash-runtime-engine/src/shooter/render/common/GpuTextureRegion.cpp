#include <shooter/render/common/GpuTextureRegion.h>

namespace shooter::render::common {
    GpuTextureRegion::GpuTextureRegion() {
        _vertex = nullptr;
        _parent = nullptr;
    }

    GpuTextureRegion *GpuTextureRegion::GpuTextureRegionConstruct(Pointer<GpuTexture> parent, Pointer<Rectangle> bounds) {
        sInt i = 0;
        _vertex = new Vector<double>();

        _vertex->insertLast(0);
        _vertex->insertLast(0);
        _vertex->insertLast(bounds->width);
        _vertex->insertLast(0);
        _vertex->insertLast(bounds->width);
        _vertex->insertLast(bounds->height);
        _vertex->insertLast(0);
        _vertex->insertLast(bounds->height);

        _vertex->insertLast((bounds->x) / parent->widthGetter());
        _vertex->insertLast((bounds->y) / parent->heightGetter());
        _vertex->insertLast((bounds->x + bounds->width) / parent->widthGetter());
        _vertex->insertLast((bounds->y) / parent->heightGetter());
        _vertex->insertLast((bounds->x + bounds->width) / parent->widthGetter());
        _vertex->insertLast((bounds->y + bounds->height) / parent->heightGetter());
        _vertex->insertLast((bounds->x) / parent->widthGetter());
        _vertex->insertLast((bounds->y + bounds->height) / parent->heightGetter());

        /*for (i = sInt(8); i < sInt(16); i++) {
            _vertex->insertAt((uInt)i, _vertex->obtainAt((uInt)i) / parent->factorGetter());
        }*/
        _parent = parent;
        return this;
    }

    Pointer<Vector<double>> GpuTextureRegion::vertexGetter() {
        return _vertex;
    }

    Pointer<GpuTexture> GpuTextureRegion::parentGetter() {
        return _parent;
    }

    GpuTextureRegion::~GpuTextureRegion() {
    }
}

