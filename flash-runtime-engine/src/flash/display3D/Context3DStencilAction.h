#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_STENCIL_ACTION_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_STENCIL_ACTION_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DStencilAction final {
        public:
            static runtime::Canvas::StencilAction translate(const String &value);
            static const sByte *DECREMENT_SATURATE;
            static const sByte *DECREMENT_WRAP;
            static const sByte *INCREMENT_SATURATE;
            static const sByte *INCREMENT_WRAP;
            static const sByte *INVERT;
            static const sByte *KEEP;
            static const sByte *SET;
            static const sByte *ZERO;
    };
}

#endif
