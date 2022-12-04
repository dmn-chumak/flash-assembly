#include <flash/display3D/Context3DCompareMode.h>

namespace flash::display3D {
    const sByte *Context3DCompareMode::ALWAYS          = "always";
    const sByte *Context3DCompareMode::EQUAL           = "equal";
    const sByte *Context3DCompareMode::GREATER         = "greater";
    const sByte *Context3DCompareMode::GREATER_EQUAL   = "greaterEqual";
    const sByte *Context3DCompareMode::LESS            = "less";
    const sByte *Context3DCompareMode::LESS_EQUAL      = "lessEqual";
    const sByte *Context3DCompareMode::NEVER           = "never";
    const sByte *Context3DCompareMode::NOT_EQUAL       = "notEqual";

    runtime::Canvas::CompareMode Context3DCompareMode::translate(const String &value) {
        if (value == ALWAYS)                return runtime::Canvas::CompareMode::ALWAYS;
        else if (value == EQUAL)            return runtime::Canvas::CompareMode::EQUAL;
        else if (value == GREATER)          return runtime::Canvas::CompareMode::GREATER;
        else if (value == GREATER_EQUAL)    return runtime::Canvas::CompareMode::GEQUAL;
        else if (value == LESS)             return runtime::Canvas::CompareMode::LESS;
        else if (value == LESS_EQUAL)       return runtime::Canvas::CompareMode::LEQUAL;
        else if (value == NEVER)            return runtime::Canvas::CompareMode::NEVER;
        else if (value == NOT_EQUAL)        return runtime::Canvas::CompareMode::NOTEQUAL;
        else                                return runtime::Canvas::CompareMode();
    }
}