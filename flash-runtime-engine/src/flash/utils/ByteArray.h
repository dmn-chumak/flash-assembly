#ifndef FLASH_UTILS_BYTE_ARRAY_H
#define FLASH_UTILS_BYTE_ARRAY_H

#include <flash/utils/IDataInput.h>
#include <flash/utils/IDataOutput.h>
#include <flash/core/Core.h>

namespace flash::utils {
    /**
     * Class represents array of bytes with interface to writing and reading simple types
     * Provides sequential access indexing implemented in Netty.IO ByteBuf:
     *
     * +-------------------+------------------+------------------+
     * |                   |                  |                  |
     * | discardable bytes |  readable bytes  |  writable bytes  |
     * |                   |                  |                  |
     * +-------------------+------------------+------------------+
     * |                   |                  |                  |
     * 0      <=       position      <=    length      <=    capacity
     * |                   |                  |                  |
     * +-------------------+------------------+------------------+
     */
    class ByteArray : public IDataInput, public IDataOutput, public Object {
        private:
            RawArrPtr<sByte>    _source;
            sByte              *_endian;
            heap                _position;
            heap                _capacity;
            heap                _length;

        public:
            ByteArray();
            ByteArray(sByte *source, const heap length);
            ByteArray(RawArrPtr<sByte> source, const heap length);
            ByteArray(const ByteArray &array);
            ByteArray(ByteArray &&array);
           ~ByteArray() override;

        public:
            void writeRawBytes(const sByte *bytes, const heap length, const bool primitive = false);
            void writeBytes(const Pointer<ByteArray> &source, const heap offset = 0, const heap length = 0);
            void writeMultiByte(const String &value, const String &charset) override;
            void writeUTFBytes(const String &value) override;
            void writeUTF(const String &value) override;
            void writeUnsignedShort(const uShort value) override;
            void writeUnsignedByte(const uByte value) override;
            void writeUnsignedInt(const uInt value) override;
            void writeBoolean(const bool value) override;
            void writeDouble(const double value) override;
            void writeFloat(const float value) override;
            void writeShort(const sShort value) override;
            void writeByte(const sByte value) override;
            void writeInt(const sInt value) override;

            void readRawBytes(sByte *bytes, const heap length, const bool primitive = false);
            void readBytes(Pointer<ByteArray> &source, const heap offset = 0, const heap length = 0);
            String readMultiByte(const heap length, const String &charset) override;
            String readUTFBytes(const heap length) override;
            String readUTF() override;
            uShort readUnsignedShort() override;
            uByte readUnsignedByte() override;
            uInt readUnsignedInt() override;
            bool readBoolean() override;
            double readDouble() override;
            float readFloat() override;
            sShort readShort() override;
            sByte readByte() override;
            sInt readInt() override;

            void uncompress(const String &algorithm);
            void compress(const String &algorithm);
            void discard();
            void deflate();
            void inflate();
            void clear();

        public:
            void position(const heap value);
            void endian(const sByte *value);
            void length(const heap value);
            heap bytesAvailable() const;
            heap position() const;
            const sByte *source() const;
            sByte *endian() const;
            heap length() const;

        private:
            template<class Type> inline void encodePrimitive(Type value);
            template<class Type> inline Type decodePrimitive();
            void ensureCapacity(const heap capacity);
    };
}

#endif
