#ifndef FLASH_DISPLAY_3D_TEXTURE_3D_H
#define FLASH_DISPLAY_3D_TEXTURE_3D_H

#include <flash/display/BitmapData.h>
#include <flash/display3D/TextureBase3D.h>
#include <flash/core/Core.h>
#include <flash/utils/ByteArray.h>

namespace flash::display3D {
    class Texture3D : public TextureBase3D {
        private:
            sInt _frameBufferID;
            uInt _imageID;
            sInt _textureID;
            uInt _width;
            uInt _height;

        public:
            Texture3D(uInt width, uInt height);
           ~Texture3D() override;

        public:
            void uploadFromBitmapData(const Pointer<display::BitmapData> &source, uInt mipLevel = 0);
            void uploadFromByteArray(const Pointer<utils::ByteArray> &bytes, uInt mipLevel = 0);
            void createRenderTexture();
            void dispose();

        public:
            uInt height() const;
            uInt width() const;
            sInt frameBufferID() const;
            sInt textureID() const;
    };
}

#endif
