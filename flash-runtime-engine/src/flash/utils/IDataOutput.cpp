#include <flash/utils/IDataOutput.h>

namespace flash::utils {
    IDataOutput::~IDataOutput() {
        // empty interface
    }

    void IDataOutput::writeMultiByte(const String &value, const String &charset) {
        // empty interface
    }

    void IDataOutput::writeUTFBytes(const String &value) {
        // empty interface
    }

    void IDataOutput::writeUTF(const String &value) {
        // empty interface
    }

    void IDataOutput::writeUnsignedShort(const uShort value) {
        // empty interface
    }

    void IDataOutput::writeUnsignedByte(const uByte value) {
        // empty interface
    }

    void IDataOutput::writeUnsignedInt(const uInt value) {
        // empty interface
    }

    void IDataOutput::writeBoolean(const bool value) {
        // empty interface
    }

    void IDataOutput::writeDouble(const double value) {
        // empty interface
    }

    void IDataOutput::writeFloat(const float value) {
        // empty interface
    }

    void IDataOutput::writeShort(const sShort value) {
        // empty interface
    }

    void IDataOutput::writeByte(const sByte value) {
        // empty interface
    }

    void IDataOutput::writeInt(const sInt value) {
        // empty interface
    }
}
