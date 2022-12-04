#include <flash/display3D/Context3DClearMask.h>

namespace flash::display3D {
    const uInt Context3DClearMask::COLOR    = 0b00000001;
    const uInt Context3DClearMask::DEPTH    = 0b00000010;
    const uInt Context3DClearMask::STENCIL  = 0b00000100;
    const uInt Context3DClearMask::ALL      = 0b00000111;

    runtime::Canvas::ClearMask Context3DClearMask::translate(const uInt value) {
        uInt result = (uInt)runtime::Canvas::ClearMask::NONE;

        if ((value & DEPTH) != 0) {
            result |= (uInt)runtime::Canvas::ClearMask::DEPTH;
        }

        if ((value & STENCIL) != 0) {
            result |= (uInt)runtime::Canvas::ClearMask::STENCIL;
        }

        if ((value & COLOR) != 0) {
            result |= (uInt)runtime::Canvas::ClearMask::COLOR;
        }

        return (runtime::Canvas::ClearMask)result;
    }
}