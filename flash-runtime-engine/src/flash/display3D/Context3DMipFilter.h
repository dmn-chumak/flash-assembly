#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_MIP_FILTER_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_MIP_FILTER_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DMipFilter final {
        public:
            static runtime::Canvas::TextureMipFilter translate(const String &value);
            static const sByte *MIPLINEAR;
            static const sByte *MIPNEAREST;
            static const sByte *MIPNONE;
    };
}

#endif
