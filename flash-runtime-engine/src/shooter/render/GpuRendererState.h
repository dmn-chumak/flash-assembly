#ifndef SHOOTER_RENDER_GPU_RENDERER_STATE_H
#define SHOOTER_RENDER_GPU_RENDERER_STATE_H

#include <flash/geometry/Matrix.h>
#include <flash/core/Core.h>
#include <shooter/render/DisplayObject.h>

using flash::geometry::Matrix;

namespace shooter::render {
    class GpuRendererState : public Object {
        private:
        protected:
        public:
            Pointer<DisplayObject> object;
            Pointer<Matrix> matrix;
            GpuRendererState();
            GpuRendererState *GpuRendererStateConstruct();
            virtual ~GpuRendererState() override;
    };
}

#endif

