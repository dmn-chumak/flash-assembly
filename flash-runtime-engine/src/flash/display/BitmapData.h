#ifndef FLASH_DISPLAY_BITMAP_DATA_H
#define FLASH_DISPLAY_BITMAP_DATA_H

#include <flash/display/IBitmapDrawable.h>
#include <flash/core/Core.h>
#include <flash/geometry/Rectangle.h>
#include <flash/utils/ByteArray.h>

namespace flash::display {
    class BitmapData : public Object, public IBitmapDrawable {
        private:
            bool _transparent;
            sInt _width;
            sInt _height;

        public:
            Pointer<utils::ByteArray> bytes;

        public:
            BitmapData(sInt width, sInt height, bool transparent = true, uInt fillColor = 0xFFFFFF);
           ~BitmapData() override;

        public:
            sInt width() const;
            Pointer<geometry::Rectangle> rectangle()  const;
            bool transparent() const;
            sInt height() const;
    };
}

#endif
