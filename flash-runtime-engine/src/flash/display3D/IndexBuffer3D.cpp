#include <flash/display3D/Context3DBufferUsage.h>
#include <flash/display3D/IndexBuffer3D.h>

namespace flash::display3D {
    IndexBuffer3D::IndexBuffer3D(sInt numIndices, const String &bufferUsage) {
        _numIndices = numIndices;
        _bufferUsage = Context3DBufferUsage::translate(bufferUsage);
        _bufferID = runtime::Canvas::createBuffer();

        runtime::Canvas::bindBuffer(runtime::Canvas::BufferTarget::ELEMENT_ARRAY_BUFFER, _bufferID);
        runtime::Canvas::bufferData(runtime::Canvas::BufferTarget::ELEMENT_ARRAY_BUFFER, nullptr, (heap)(_numIndices * 2), _bufferUsage);
    }

    IndexBuffer3D::~IndexBuffer3D() {
        dispose();
    }

    void IndexBuffer3D::uploadFromBytes(const sByte *data, sInt startIndex, sInt numIndices) {
        runtime::Canvas::bindBuffer(runtime::Canvas::BufferTarget::ELEMENT_ARRAY_BUFFER, _bufferID);
        runtime::Canvas::bufferData(runtime::Canvas::BufferTarget::ELEMENT_ARRAY_BUFFER, data, (heap)(_numIndices * 2), _bufferUsage);
    }

    void IndexBuffer3D::uploadFromByteArray(const Pointer<utils::ByteArray> &data, sInt byteArrayOffset, sInt startIndex, sInt numIndices) {
        uploadFromBytes(data->source() + byteArrayOffset, startIndex, numIndices);
    }

    void IndexBuffer3D::uploadFromVector(const Pointer<Vector<uShort>> &data, sInt startIndex, sInt numIndices) {
        uploadFromBytes((const sByte *)data->source(), startIndex, numIndices);
    }

    void IndexBuffer3D::dispose() {
        runtime::Canvas::deleteBuffer(_bufferID);
    }

    sInt IndexBuffer3D::numIndices() const {
        return _numIndices;
    }

    sInt IndexBuffer3D::bufferID() const {
        return _bufferID;
    }
}