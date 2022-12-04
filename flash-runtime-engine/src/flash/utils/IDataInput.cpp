#include <flash/utils/IDataInput.h>

namespace flash::utils {
    IDataInput::~IDataInput() {
        // empty interface
    }

    String IDataInput::readMultiByte(const uInt length, const String &charset) {
        // empty interface
        return nullptr;
    }

    String IDataInput::readUTFBytes(const uInt length) {
        // empty interface
        return nullptr;
    }

    String IDataInput::readUTF() {
        // empty interface
        return nullptr;
    }

    uShort IDataInput::readUnsignedShort() {
        // empty interface
        return 0;
    }

    uByte IDataInput::readUnsignedByte() {
        // empty interface
        return 0;
    }

    uInt IDataInput::readUnsignedInt() {
        // empty interface
        return 0;
    }

    bool IDataInput::readBoolean() {
        // empty interface
        return false;
    }

    double IDataInput::readDouble() {
        // empty interface
        return 0;
    }

    float IDataInput::readFloat() {
        // empty interface
        return 0;
    }

    sShort IDataInput::readShort() {
        // empty interface
        return 0;
    }

    sByte IDataInput::readByte() {
        // empty interface
        return 0;
    }

    sInt IDataInput::readInt() {
        // empty interface
        return 0;
    }
}
