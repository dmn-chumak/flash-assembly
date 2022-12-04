#ifndef FLASH_DISPLAY_BITMAP_ENCODING_COLOR_SPACE_H
#define FLASH_DISPLAY_BITMAP_ENCODING_COLOR_SPACE_H

#include <flash/core/Core.h>

namespace flash::display {
    class BitmapEncodingColorSpace final {
        public:
            static const sByte *COLORSPACE_4_2_0;
            static const sByte *COLORSPACE_4_2_2;
            static const sByte *COLORSPACE_4_4_4;
            static const sByte *COLORSPACE_AUTO;
    };
}

#endif
