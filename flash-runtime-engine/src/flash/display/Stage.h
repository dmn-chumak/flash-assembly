#ifndef FLASH_DISPLAY_STAGE_H
#define FLASH_DISPLAY_STAGE_H

#include <flash/display/DisplayObjectContainer.h>
#include <flash/core/Core.h>

namespace flash::display {
    class Stage : public DisplayObjectContainer {
        public:
            Stage();
           ~Stage() override;
    };
}

#endif
