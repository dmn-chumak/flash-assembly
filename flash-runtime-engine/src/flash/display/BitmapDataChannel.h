#ifndef FLASH_DISPLAY_BITMAP_DATA_CHANNEL_H
#define FLASH_DISPLAY_BITMAP_DATA_CHANNEL_H

#include <flash/core/Core.h>

namespace flash::display {
    class BitmapDataChannel final {
        public:
            static const uInt RED;
            static const uInt GREEN;
            static const uInt BLUE;
            static const uInt ALPHA;
    };
}

#endif
