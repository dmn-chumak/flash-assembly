#ifndef FLASH_UTILS_I_DATA_OUTPUT_H
#define FLASH_UTILS_I_DATA_OUTPUT_H

#include <flash/core/Core.h>

namespace flash::utils {
    class IDataOutput {
        public:
            virtual ~IDataOutput();
            virtual void writeMultiByte(const String &value, const String &charset);
            virtual void writeUTFBytes(const String &value);
            virtual void writeUTF(const String &value);
            virtual void writeUnsignedShort(const uShort value);
            virtual void writeUnsignedByte(const uByte value);
            virtual void writeUnsignedInt(const uInt value);
            virtual void writeBoolean(const bool value);
            virtual void writeDouble(const double value);
            virtual void writeFloat(const float value);
            virtual void writeShort(const sShort value);
            virtual void writeByte(const sByte value);
            virtual void writeInt(const sInt value);
    };
}

#endif
