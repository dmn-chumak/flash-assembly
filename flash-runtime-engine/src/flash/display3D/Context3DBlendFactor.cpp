#include <flash/display3D/Context3DBlendFactor.h>

namespace flash::display3D {
    const sByte *Context3DBlendFactor::DESTINATION_ALPHA           = "destinationAlpha";
    const sByte *Context3DBlendFactor::DESTINATION_COLOR           = "destinationColor";
    const sByte *Context3DBlendFactor::ONE                         = "one";
    const sByte *Context3DBlendFactor::ONE_MINUS_DESTINATION_ALPHA = "oneMinusDestinationAlpha";
    const sByte *Context3DBlendFactor::ONE_MINUS_DESTINATION_COLOR = "oneMinusDestinationColor";
    const sByte *Context3DBlendFactor::ONE_MINUS_SOURCE_ALPHA      = "oneMinusSourceAlpha";
    const sByte *Context3DBlendFactor::ONE_MINUS_SOURCE_COLOR      = "oneMinusSourceColor";
    const sByte *Context3DBlendFactor::SOURCE_ALPHA                = "sourceAlpha";
    const sByte *Context3DBlendFactor::SOURCE_COLOR                = "sourceColor";
    const sByte *Context3DBlendFactor::ZERO                        = "zero";

    runtime::Canvas::BlendFactor Context3DBlendFactor::translate(const String &value) {
        if (value == DESTINATION_ALPHA)                 return runtime::Canvas::BlendFactor::DST_ALPHA;
        else if (value == DESTINATION_COLOR)            return runtime::Canvas::BlendFactor::DST_COLOR;
        else if (value == ONE)                          return runtime::Canvas::BlendFactor::ONE;
        else if (value == ONE_MINUS_DESTINATION_ALPHA)  return runtime::Canvas::BlendFactor::ONE_MINUS_DST_ALPHA;
        else if (value == ONE_MINUS_DESTINATION_COLOR)  return runtime::Canvas::BlendFactor::ONE_MINUS_DST_COLOR;
        else if (value == ONE_MINUS_SOURCE_ALPHA)       return runtime::Canvas::BlendFactor::ONE_MINUS_SRC_ALPHA;
        else if (value == ONE_MINUS_SOURCE_COLOR)       return runtime::Canvas::BlendFactor::ONE_MINUS_SRC_COLOR;
        else if (value == SOURCE_ALPHA)                 return runtime::Canvas::BlendFactor::SRC_ALPHA;
        else if (value == SOURCE_COLOR)                 return runtime::Canvas::BlendFactor::SRC_COLOR;
        else if (value == ZERO)                         return runtime::Canvas::BlendFactor::ZERO;
        else                                            return runtime::Canvas::BlendFactor();
    }
}