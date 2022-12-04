#include <flash/display3D/Texture3D.h>
#include <flash/runtime/Canvas.h>

using flash::runtime::Canvas::TextureTarget;
using flash::runtime::Canvas::TextureParameter;
using flash::runtime::Canvas::TextureFilter;
using flash::runtime::Canvas::TextureWrapMode;
using flash::runtime::Canvas::BufferTarget;
using flash::runtime::Canvas::BufferAttachment;

namespace flash::display3D {
    Texture3D::Texture3D(uInt width, uInt height) {
        _textureID = runtime::Canvas::createTexture();
        _width = width;
        _height = height;
    }

    Texture3D::~Texture3D() {
        dispose();
    }

    void Texture3D::uploadFromBitmapData(const Pointer<display::BitmapData> &source, uInt mipLevel) {
        uploadFromByteArray(source->bytes);
    }

    void Texture3D::uploadFromByteArray(const Pointer<utils::ByteArray> &bytes, uInt mipLevel) {
        runtime::Canvas::bindTexture(TextureTarget::TEXTURE_2D, _textureID);
        runtime::Canvas::texImage2D(TextureTarget::TEXTURE_2D, mipLevel, _width, _height, bytes->source(), bytes->length());
        runtime::Canvas::generateMipmap(TextureTarget::TEXTURE_2D);
    }

    void Texture3D::createRenderTexture() {
        runtime::Canvas::bindTexture(TextureTarget::TEXTURE_2D, _textureID);
        runtime::Canvas::texImage2D(TextureTarget::TEXTURE_2D, 0, _width, _height, nullptr, 0);

        runtime::Canvas::texParameterI(TextureTarget::TEXTURE_2D, TextureParameter::MIN_FILTER, (sInt)TextureFilter::NEAREST);
        runtime::Canvas::texParameterI(TextureTarget::TEXTURE_2D, TextureParameter::MAG_FILTER, (sInt)TextureFilter::NEAREST);
        runtime::Canvas::texParameterI(TextureTarget::TEXTURE_2D, TextureParameter::WRAP_S, (sInt)TextureWrapMode::CLAMP_TO_EDGE);
        runtime::Canvas::texParameterI(TextureTarget::TEXTURE_2D, TextureParameter::WRAP_T, (sInt)TextureWrapMode::CLAMP_TO_EDGE);

        _frameBufferID = runtime::Canvas::createFrameBuffer();
        runtime::Canvas::bindFrameBuffer(BufferTarget::FRAME_BUFFER, _frameBufferID);
        runtime::Canvas::frameBufferTexture2D(BufferTarget::FRAME_BUFFER, BufferAttachment::COLOR_ATTACHMENT, TextureTarget::TEXTURE_2D, _textureID, 0);
    }

    void Texture3D::dispose() {
        runtime::Canvas::deleteTexture(_textureID);
    }

    uInt Texture3D::height() const {
        return _height;
    }

    uInt Texture3D::width() const {
        return _width;
    }

    sInt Texture3D::frameBufferID() const {
        return _frameBufferID;
    }

    sInt Texture3D::textureID() const {
        return _textureID;
    }
}