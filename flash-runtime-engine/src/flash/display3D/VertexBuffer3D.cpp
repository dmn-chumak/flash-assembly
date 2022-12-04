#include <flash/display3D/Context3DBufferUsage.h>
#include <flash/display3D/VertexBuffer3D.h>

namespace flash::display3D {
    VertexBuffer3D::VertexBuffer3D(uInt numVertices, uInt data32PerVertex, const String &bufferUsage) {
        _numVertices = numVertices;
        _data32PerVertex = data32PerVertex;
        _bufferUsage = Context3DBufferUsage::translate(bufferUsage);
        _bufferID = runtime::Canvas::createBuffer();

        runtime::Canvas::bindBuffer(runtime::Canvas::BufferTarget::ARRAY_BUFFER, _bufferID);
        runtime::Canvas::bufferData(runtime::Canvas::BufferTarget::ARRAY_BUFFER, nullptr, _numVertices * _data32PerVertex * 4, _bufferUsage);
    }

    VertexBuffer3D::~VertexBuffer3D() {
        dispose();
    }

    void VertexBuffer3D::uploadFromBytes(const sByte *data, sInt startVertex, sInt numVertices) {
        runtime::Canvas::bindBuffer(runtime::Canvas::BufferTarget::ARRAY_BUFFER, _bufferID);
        runtime::Canvas::bufferData(runtime::Canvas::BufferTarget::ARRAY_BUFFER, data, _numVertices * _data32PerVertex * 4, _bufferUsage);
    }

    void VertexBuffer3D::uploadFromByteArray(const Pointer<utils::ByteArray> &data, sInt byteArrayOffset, sInt startVertex, sInt numVertices) {
        uploadFromBytes(data->source() + byteArrayOffset, startVertex, numVertices);
    }

    void VertexBuffer3D::uploadFromVector(const Pointer<Vector<float>> &data, sInt startVertex, sInt numVertices) {
        uploadFromBytes((const sByte *)data->source(), startVertex, numVertices);
    }

    void VertexBuffer3D::dispose() {
        runtime::Canvas::deleteBuffer(_bufferID);
    }

    uInt VertexBuffer3D::data32PerVertex() const {
        return _data32PerVertex;
    }

    uInt VertexBuffer3D::numVertices() const {
        return _numVertices;
    }

    sInt VertexBuffer3D::bufferID() const {
        return _bufferID;
    }
}
