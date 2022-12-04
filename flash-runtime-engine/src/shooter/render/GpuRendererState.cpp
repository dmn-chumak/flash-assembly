#include <shooter/render/GpuRendererState.h>

namespace shooter::render {
    GpuRendererState::GpuRendererState() {
        object = nullptr;
        matrix = nullptr;
    }

    GpuRendererState *GpuRendererState::GpuRendererStateConstruct() {
        matrix = new Matrix();
        return this;
    }

    GpuRendererState::~GpuRendererState() {
    }
}

