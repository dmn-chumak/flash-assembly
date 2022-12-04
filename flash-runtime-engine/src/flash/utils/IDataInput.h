#ifndef FLASH_UTILS_I_DATA_INPUT_H
#define FLASH_UTILS_I_DATA_INPUT_H

#include <flash/core/Core.h>

namespace flash::utils {
    class IDataInput {
        public:
            virtual ~IDataInput();
            virtual String readMultiByte(const uInt length, const String &charset);
            virtual String readUTFBytes(const uInt length);
            virtual String readUTF();
            virtual uShort readUnsignedShort();
            virtual uByte readUnsignedByte();
            virtual uInt readUnsignedInt();
            virtual bool readBoolean();
            virtual double readDouble();
            virtual float readFloat();
            virtual sShort readShort();
            virtual sByte readByte();
            virtual sInt readInt();
    };
}

#endif
