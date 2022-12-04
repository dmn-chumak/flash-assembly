#include <flash/display3D/Context3DTextureFilter.h>

namespace flash::display3D {
    const sByte *Context3DTextureFilter::ANISOTROPIC16X    = "anisotropic16x";
    const sByte *Context3DTextureFilter::ANISOTROPIC8X     = "anisotropic8x";
    const sByte *Context3DTextureFilter::ANISOTROPIC4X     = "anisotropic4x";
    const sByte *Context3DTextureFilter::ANISOTROPIC2X     = "anisotropic2x";
    const sByte *Context3DTextureFilter::LINEAR            = "linear";
    const sByte *Context3DTextureFilter::NEAREST           = "nearest";

    runtime::Canvas::TextureFilter Context3DTextureFilter::translate(const String &value) {
        if (value == LINEAR)        return runtime::Canvas::TextureFilter::LINEAR;
        else if (value == NEAREST)  return runtime::Canvas::TextureFilter::NEAREST;
        else                        return runtime::Canvas::TextureFilter();
    }
}