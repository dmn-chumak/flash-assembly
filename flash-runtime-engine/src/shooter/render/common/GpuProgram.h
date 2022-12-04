#ifndef SHOOTER_RENDER_COMMON_GPU_PROGRAM_H
#define SHOOTER_RENDER_COMMON_GPU_PROGRAM_H

#include <flash/display3D/Context3D.h>
#include <flash/display3D/Context3DProgramType.h>
#include <flash/display3D/Program3D.h>
#include <flash/core/Core.h>

using flash::display3D::Context3D;
using flash::display3D::Context3DProgramType;
using flash::display3D::Program3D;

namespace shooter::render::common {
    class GpuProgram : public Object {
        private:
            Pointer<Program3D> _parent;
        public:
            GpuProgram();
            GpuProgram *GpuProgramConstruct(Pointer<Context3D> context3D, String vertex, String fragment);
            Pointer<Program3D> parentGetter();
            virtual ~GpuProgram() override;
    };
}

#endif

