#include <flash/display3D/Context3DWrapMode.h>

namespace flash::display3D {
    const sByte *Context3DWrapMode::CLAMP              = "clamp";
    const sByte *Context3DWrapMode::CLAMP_U_REPEAT_V   = "clamp_u_repeat_v";
    const sByte *Context3DWrapMode::REPEAT             = "repeat";
    const sByte *Context3DWrapMode::REPEAT_U_CLAMP_V   = "repeat_u_clamp_v";

    runtime::Canvas::TextureWrapMode Context3DWrapMode::translateU(const String &value) {
        if (value == CLAMP)                 return runtime::Canvas::TextureWrapMode::CLAMP_TO_EDGE;
        else if (value == CLAMP_U_REPEAT_V) return runtime::Canvas::TextureWrapMode::CLAMP_TO_EDGE;
        else if (value == REPEAT)           return runtime::Canvas::TextureWrapMode::REPEAT;
        else if (value == REPEAT_U_CLAMP_V) return runtime::Canvas::TextureWrapMode::REPEAT;
        else                                return runtime::Canvas::TextureWrapMode();
    }

    runtime::Canvas::TextureWrapMode Context3DWrapMode::translateV(const String &value) {
        if (value == CLAMP)                 return runtime::Canvas::TextureWrapMode::CLAMP_TO_EDGE;
        else if (value == CLAMP_U_REPEAT_V) return runtime::Canvas::TextureWrapMode::REPEAT;
        else if (value == REPEAT)           return runtime::Canvas::TextureWrapMode::REPEAT;
        else if (value == REPEAT_U_CLAMP_V) return runtime::Canvas::TextureWrapMode::CLAMP_TO_EDGE;
        else                                return runtime::Canvas::TextureWrapMode();
    }
}
