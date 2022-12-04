#ifndef FLASH_DISPLAY_3D_STAGE_3D_H
#define FLASH_DISPLAY_3D_STAGE_3D_H

#include <flash/events/EventDispatcher.h>
#include <flash/display3D/Context3D.h>
#include <flash/core/Core.h>

namespace flash::display3D {
    class Stage3D : public events::EventDispatcher {
        private:
            sInt _stageID;

        public:
            Pointer<Context3D> requestContext3D();
            Pointer<Context3D> context3D;

        public:
            Stage3D(sInt stageID);
           ~Stage3D() override;
    };
}

#endif
