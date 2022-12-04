#ifndef FLASH_DISPLAY_3D_INDEX_BUFFER_3D_H
#define FLASH_DISPLAY_3D_INDEX_BUFFER_3D_H

#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>
#include <flash/utils/ByteArray.h>

namespace flash::display3D {
    class IndexBuffer3D final : public Object {
        private:
            sInt _numIndices;
            runtime::Canvas::BufferUsage _bufferUsage;
            sInt _bufferID;

        public:
            IndexBuffer3D(sInt numIndices, const String &bufferUsage);
           ~IndexBuffer3D() override;

        public:
            void uploadFromBytes(const sByte *data, sInt startIndex, sInt numIndices);
            void uploadFromByteArray(const Pointer<utils::ByteArray> &data, sInt byteArrayOffset, sInt startIndex, sInt numIndices);
            void uploadFromVector(const Pointer<Vector<uShort>> &data, sInt startIndex, sInt numIndices);
            void dispose();

        public:
            sInt numIndices() const;
            sInt bufferID() const;
    };
}

#endif
