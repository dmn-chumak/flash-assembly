#include <flash/network/Socket.h>
#include <flash/runtime/Network.h>
#include <flash/events/IOErrorEvent.h>
#include <flash/events/ProgressEvent.h>

using flash::events::Event;
using flash::events::IOErrorEvent;
using flash::events::ProgressEvent;
using flash::utils::ByteArray;

namespace flash::network {
    const sInt Socket::INTERNAL_CONNECT_EVENT       = 0;
    const sInt Socket::INTERNAL_CLOSE_EVENT         = 1;
    const sInt Socket::INTERNAL_SOCKET_DATA_EVENT   = 2;
    const sInt Socket::INTERNAL_IO_ERROR_EVENT      = 3;

    Socket::Socket(const String &host, sInt port) {
        _socketID = runtime::Network::createSocket(
            (void *)Socket::globalEventCallback,
            this
        );

        _isConnecting = false;
        _isConnected = false;
        _readerSource = new ByteArray();
        _writerSource = new ByteArray();
        _refCount++;

        connect(host, port);
    }

    Socket::~Socket() {
        runtime::Network::deleteSocket(_socketID);
    }

    void Socket::globalEventCallback(Socket *socket, sInt event, heap first) {
        socket->localEventCallback(event, first);
    }

    void Socket::localEventCallback(sInt event, heap first) {
        switch (event) {
            case INTERNAL_CONNECT_EVENT: {
                dispatchEvent(new Event(Event::CONNECT));

                _isConnecting = false;
                _isConnected = true;

                break;
            }

            case INTERNAL_CLOSE_EVENT: {
                dispatchEvent(new Event(Event::CLOSE));
                _isConnected = false;

                break;
            }

            case INTERNAL_SOCKET_DATA_EVENT: {
                RawArrPtr<sByte> buffer = new sByte[first];
                runtime::Network::bindSocketData(_socketID, buffer.get(), first);

                _readerSource->writeRawBytes(buffer.get(), first);
                _readerSource->position(_readerSource->position() - first);
                dispatchEvent(new ProgressEvent(ProgressEvent::SOCKET_DATA));
                _readerSource->discard();

                break;
            }

            case INTERNAL_IO_ERROR_EVENT: {
                dispatchEvent(new IOErrorEvent(IOErrorEvent::IO_ERROR));
                _isConnecting = false;

                break;
            }
        }
    }

    void Socket::connect(const String &host, sInt port) {
        if (host != nullptr && port != 0) {
            if (_isConnecting) {
                return;
            }

            runtime::Network::openSocketConnection(_socketID, host.source(), host.length(), port);
            _isConnecting = true;
        }
    }

    void Socket::close() {
        if (_isConnected) {
            runtime::Network::closeSocketConnection(_socketID);
        }
    }

    void Socket::flush() {
        runtime::Network::sendSocketData(_socketID, _writerSource->source(), _writerSource->length());
        _writerSource->discard();
    }

    uInt Socket::bytesAvailable() {
        return _readerSource->bytesAvailable();
    }

    uInt Socket::bytesPending() {
        return _writerSource->position();
    }

    bool Socket::connected() {
        return _isConnected;
    }

    void Socket::writeRawBytes(const sByte *bytes, const heap length, const bool primitive) {
        _writerSource->writeRawBytes(bytes, length, primitive);
    }

    void Socket::writeBytes(const Pointer<ByteArray> &source, const heap offset, const heap length) {
        _writerSource->writeBytes(source, offset, length);
    }

    void Socket::writeMultiByte(const String &value, const String &charset) {
        _writerSource->writeMultiByte(value, charset);
    }

    void Socket::writeUTFBytes(const String &value) {
        _writerSource->writeUTFBytes(value);
    }

    void Socket::writeUTF(const String &value) {
        _writerSource->writeUTF(value);
    }

    void Socket::writeUnsignedShort(const uShort value) {
        _writerSource->writeUnsignedShort(value);
    }

    void Socket::writeUnsignedByte(const uByte value) {
        _writerSource->writeUnsignedByte(value);
    }

    void Socket::writeUnsignedInt(const uInt value) {
        _writerSource->writeUnsignedInt(value);
    }

    void Socket::writeBoolean(const bool value) {
        _writerSource->writeBoolean(value);
    }

    void Socket::writeDouble(const double value) {
        _writerSource->writeDouble(value);
    }

    void Socket::writeFloat(const float value) {
        _writerSource->writeFloat(value);
    }

    void Socket::writeShort(const sShort value) {
        _writerSource->writeShort(value);
    }

    void Socket::writeByte(const sByte value) {
        _writerSource->writeByte(value);
    }

    void Socket::writeInt(const sInt value) {
        _writerSource->writeInt(value);
    }

    void Socket::readRawBytes(sByte *bytes, const heap length, const bool primitive) {
        _readerSource->readRawBytes(bytes, length, primitive);
    }

    void Socket::readBytes(Pointer<ByteArray> &source, const heap offset, const heap length) {
        _readerSource->readBytes(source, offset, length);
    }

    String Socket::readMultiByte(const heap length, const String &charset) {
        return _readerSource->readMultiByte(length, charset);
    }

    String Socket::readUTFBytes(const heap length) {
        return _readerSource->readUTFBytes(length);
    }

    String Socket::readUTF() {
        return _readerSource->readUTF();
    }

    uShort Socket::readUnsignedShort() {
        return _readerSource->readUnsignedShort();
    }

    uByte Socket::readUnsignedByte() {
        return _readerSource->readUnsignedByte();
    }

    uInt Socket::readUnsignedInt() {
        return _readerSource->readUnsignedInt();
    }

    bool Socket::readBoolean() {
        return _readerSource->readBoolean();
    }

    double Socket::readDouble() {
        return _readerSource->readDouble();
    }

    float Socket::readFloat() {
        return _readerSource->readFloat();
    }

    sShort Socket::readShort() {
        return _readerSource->readShort();
    }

    sByte Socket::readByte() {
        return _readerSource->readByte();
    }

    sInt Socket::readInt() {
        return _readerSource->readInt();
    }
}
