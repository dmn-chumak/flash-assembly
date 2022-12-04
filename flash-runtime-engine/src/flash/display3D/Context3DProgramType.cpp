#include <flash/display3D/Context3DProgramType.h>

namespace flash::display3D {
    const sByte *Context3DProgramType::FRAGMENT    = "fragment";
    const sByte *Context3DProgramType::VERTEX      = "vertex";

    runtime::Canvas::ProgramType Context3DProgramType::translate(const String &value) {
        if (value == FRAGMENT)      return runtime::Canvas::ProgramType::FRAGMENT_SHADER;
        else if (value == VERTEX)   return runtime::Canvas::ProgramType::VERTEX_SHADER;
        else                        return runtime::Canvas::ProgramType();
    }
}