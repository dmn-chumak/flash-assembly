#ifndef FLASH_NETWORK_SOCKET_H
#define FLASH_NETWORK_SOCKET_H

#include <flash/utils/IDataInput.h>
#include <flash/utils/IDataOutput.h>
#include <flash/utils/ByteArray.h>
#include <flash/events/EventDispatcher.h>
#include <flash/core/Core.h>

namespace flash::network {
    class Socket : public utils::IDataInput, public utils::IDataOutput, public events::EventDispatcher {
        private:
            static const sInt INTERNAL_CONNECT_EVENT;
            static const sInt INTERNAL_CLOSE_EVENT;
            static const sInt INTERNAL_SOCKET_DATA_EVENT;
            static const sInt INTERNAL_IO_ERROR_EVENT;

        private:
            bool _isConnecting;
            bool _isConnected;
            Pointer<utils::ByteArray> _readerSource;
            Pointer<utils::ByteArray> _writerSource;
            sInt _socketID;

        private:
            static void globalEventCallback(Socket *socket, sInt event = 0, heap first = 0);
            void localEventCallback(sInt event = 0, heap first = 0);

        public:
            Socket(const String &host = nullptr, sInt port = 0);
           ~Socket() override;

        public:
            void connect(const String &host, sInt port);
            void close();
            void flush();

            uInt bytesAvailable();
            uInt bytesPending();
            bool connected();

        public:
            void writeRawBytes(const sByte *bytes, const heap length, const bool primitive = false);
            void writeBytes(const Pointer<utils::ByteArray> &source, const heap offset = 0, const heap length = 0);
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
            void readBytes(Pointer<utils::ByteArray> &source, const heap offset = 0, const heap length = 0);
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
    };
}

#endif
