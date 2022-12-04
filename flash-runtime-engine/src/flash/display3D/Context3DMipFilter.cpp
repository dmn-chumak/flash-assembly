#include <flash/display3D/Context3DMipFilter.h>

namespace flash::display3D {
    const sByte *Context3DMipFilter::MIPLINEAR     = "miplinear";
    const sByte *Context3DMipFilter::MIPNEAREST    = "mipnearest";
    const sByte *Context3DMipFilter::MIPNONE       = "mipnone";

    runtime::Canvas::TextureMipFilter Context3DMipFilter::translate(const String &value) {
        if (value == MIPLINEAR)         return runtime::Canvas::TextureMipFilter::LINEAR_MIPMAP_LINEAR;
        else if (value == MIPNEAREST)   return runtime::Canvas::TextureMipFilter::NEAREST_MIPMAP_NEAREST;
        else if (value == MIPNONE)      return runtime::Canvas::TextureMipFilter::NEAREST_MIPMAP_LINEAR;
        else                            return runtime::Canvas::TextureMipFilter();
    }
}