#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_CLEAR_MASK_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_CLEAR_MASK_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DClearMask final {
        public:
            static runtime::Canvas::ClearMask translate(const uInt value);
            static const uInt COLOR;
            static const uInt DEPTH;
            static const uInt STENCIL;
            static const uInt ALL;
    };
}

#endif
