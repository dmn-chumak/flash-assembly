#include <shooter/render/common/GpuProgram.h>

namespace shooter::render::common {
    GpuProgram::GpuProgram() {
        _parent = nullptr;
    }

    GpuProgram *GpuProgram::GpuProgramConstruct(Pointer<Context3D> context3D, String vertex, String fragment) {
        _parent = context3D->createProgram();
        _parent->upload(vertex, fragment);
        return this;
    }

    Pointer<Program3D> GpuProgram::parentGetter() {
        return _parent;
    }

    GpuProgram::~GpuProgram() {
    }
}

