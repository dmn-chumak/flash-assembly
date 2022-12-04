#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_BUFFER_USAGE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_BUFFER_USAGE_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DBufferUsage final {
        public:
            static runtime::Canvas::BufferUsage translate(const String &value);
            static const sByte *DYNAMIC_DRAW;
            static const sByte *STATIC_DRAW;
    };
}

#endif
