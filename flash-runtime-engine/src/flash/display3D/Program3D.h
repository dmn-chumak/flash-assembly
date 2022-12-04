#ifndef FLASH_DISPLAY_3D_PROGRAM_3D_H
#define FLASH_DISPLAY_3D_PROGRAM_3D_H

#include <flash/core/Core.h>

namespace flash::display3D {
    class Program3D final : public Object {
        private:
            sInt _programID;
            sInt _registersIDs[4];
            sInt _constantsIDs[4];
            sInt _samplersIDs[4];

        public:
            Program3D();
           ~Program3D() override;

        public:
            void upload(const String &vertexProgram, const String &fragmentProgram);
            void dispose();

        public:
            sInt registerID(const uInt index) const;
            sInt constantID(const uInt index) const;
            sInt samplerID(const uInt index) const;
            sInt programID() const;
    };
}

#endif
