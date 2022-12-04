#include <flash/display3D/Context3DStencilAction.h>

namespace flash::display3D {
    const sByte *Context3DStencilAction::DECREMENT_SATURATE    = "decrementSaturate";
    const sByte *Context3DStencilAction::DECREMENT_WRAP        = "decrementWrap";
    const sByte *Context3DStencilAction::INCREMENT_SATURATE    = "incrementSaturate";
    const sByte *Context3DStencilAction::INCREMENT_WRAP        = "incrementWrap";
    const sByte *Context3DStencilAction::INVERT                = "invert";
    const sByte *Context3DStencilAction::KEEP                  = "keep";
    const sByte *Context3DStencilAction::SET                   = "set";
    const sByte *Context3DStencilAction::ZERO                  = "zero";

    runtime::Canvas::StencilAction Context3DStencilAction::translate(const String &value) {
        if (value == DECREMENT_SATURATE)        return runtime::Canvas::StencilAction::DECR;
        else if (value == DECREMENT_WRAP)       return runtime::Canvas::StencilAction::DECR_WRAP;
        else if (value == INCREMENT_SATURATE)   return runtime::Canvas::StencilAction::INCR;
        else if (value == INCREMENT_WRAP)       return runtime::Canvas::StencilAction::INCR_WRAP;
        else if (value == INVERT)               return runtime::Canvas::StencilAction::INVERT;
        else if (value == KEEP)                 return runtime::Canvas::StencilAction::KEEP;
        else if (value == SET)                  return runtime::Canvas::StencilAction::REPLACE;
        else if (value == ZERO)                 return runtime::Canvas::StencilAction::ZERO;
        else                                    return runtime::Canvas::StencilAction();
    }
}