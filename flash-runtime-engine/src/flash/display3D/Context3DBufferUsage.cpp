#include <flash/display3D/Context3DBufferUsage.h>

namespace flash::display3D {
    const sByte *Context3DBufferUsage::DYNAMIC_DRAW    = "dynamicDraw";
    const sByte *Context3DBufferUsage::STATIC_DRAW     = "staticDraw";

    runtime::Canvas::BufferUsage Context3DBufferUsage::translate(const String &value) {
        if (value == DYNAMIC_DRAW)      return runtime::Canvas::BufferUsage::DYNAMIC_DRAW;
        else if (value == STATIC_DRAW)  return runtime::Canvas::BufferUsage::STATIC_DRAW;
        else                            return runtime::Canvas::BufferUsage();
    }
}