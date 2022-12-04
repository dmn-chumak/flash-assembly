#ifndef FLASH_DISPLAY_3D_VERTEX_BUFFER_3D_H
#define FLASH_DISPLAY_3D_VERTEX_BUFFER_3D_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>
#include <flash/utils/ByteArray.h>

namespace flash::display3D {
    class VertexBuffer3D final : public Object {
        private:
            uInt _numVertices;
            uInt _data32PerVertex;
            runtime::Canvas::BufferUsage _bufferUsage;
            sInt _bufferID;

        public:
            VertexBuffer3D(uInt numVertices, uInt data32PerVertex, const String &bufferUsage);
           ~VertexBuffer3D() override;

        public:
            void uploadFromBytes(const sByte *data, sInt startVertex, sInt numVertices);
            void uploadFromByteArray(const Pointer<utils::ByteArray> &data, sInt byteArrayOffset, sInt startVertex, sInt numVertices);
            void uploadFromVector(const Pointer<Vector<float>> &data, sInt startVertex, sInt numVertices);
            void dispose();

        public:
            uInt data32PerVertex() const;
            uInt numVertices() const;
            sInt bufferID() const;
    };
}

#endif
