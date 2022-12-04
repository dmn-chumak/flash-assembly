#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_VERTEX_BUFFER_FORMAT_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_VERTEX_BUFFER_FORMAT_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DVertexBufferFormat final {
        public:
            static runtime::Canvas::DataType translateType(const String &value);
            static uInt translateSize(const String &value);
            static const sByte *BYTES_4;
            static const sByte *FLOAT_4;
            static const sByte *FLOAT_3;
            static const sByte *FLOAT_2;
            static const sByte *FLOAT_1;
    };
}

#endif
