#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_PROGRAM_TYPE_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_PROGRAM_TYPE_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Context3DProgramType final {
        public:
            static runtime::Canvas::ProgramType translate(const String &value);
            static const sByte *FRAGMENT;
            static const sByte *VERTEX;
    };
}

#endif
