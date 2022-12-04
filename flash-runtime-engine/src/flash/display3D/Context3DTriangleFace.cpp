#include <flash/display3D/Context3DTriangleFace.h>

namespace flash::display3D {
    const sByte *Context3DTriangleFace::BACK           = "back";
    const sByte *Context3DTriangleFace::FRONT          = "front";
    const sByte *Context3DTriangleFace::FRONT_AND_BACK = "frontAndBack";
    const sByte *Context3DTriangleFace::NONE           = "none";

    runtime::Canvas::CullingMode Context3DTriangleFace::translate(const String &value) {
        if (value == BACK)                  return runtime::Canvas::CullingMode::BACK;
        else if (value == FRONT)            return runtime::Canvas::CullingMode::FRONT;
        else if (value == FRONT_AND_BACK)   return runtime::Canvas::CullingMode::FRONT_AND_BACK;
        else                                return runtime::Canvas::CullingMode();
    }
}