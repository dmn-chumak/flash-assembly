#include <flash/display/BitmapData.h>

namespace flash::display {
    BitmapData::BitmapData(sInt width, sInt height, bool transparent, uInt fillColor)
    : _transparent(transparent)
    , _width(width)
    , _height(height) {
        // empty
    }

    BitmapData::~BitmapData() {
        // empty
    }

    sInt BitmapData::width() const {
        return _width;
    }

    Pointer<geometry::Rectangle> BitmapData::rectangle() const {
        return new geometry::Rectangle(0, 0, _width, _height);
    }

    bool BitmapData::transparent() const {
        return _transparent;
    }

    sInt BitmapData::height() const {
        return _height;
    }
}
