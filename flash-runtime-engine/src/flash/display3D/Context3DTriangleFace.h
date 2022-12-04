#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_TRIANGLE_FACE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_TRIANGLE_FACE_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DTriangleFace final {
        public:
            static runtime::Canvas::CullingMode translate(const String &value);
            static const sByte *BACK;
            static const sByte *FRONT;
            static const sByte *FRONT_AND_BACK;
            static const sByte *NONE;
    };
}

#endif
