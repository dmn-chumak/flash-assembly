#ifndef FLASH_DISPLAY_DISPLAY_OBJECT_CONTAINER_H
#define FLASH_DISPLAY_DISPLAY_OBJECT_CONTAINER_H

#include <flash/display/InteractiveObject.h>
#include <flash/core/Core.h>

namespace flash::display {
    class DisplayObjectContainer : public InteractiveObject {
        public:
            DisplayObjectContainer();
           ~DisplayObjectContainer() override;
    };
}

#endif
