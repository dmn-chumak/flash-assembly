#ifndef FLASH_DISPLAY_INTERACTIVE_OBJECT_H
#define FLASH_DISPLAY_INTERACTIVE_OBJECT_H

#include <flash/display/DisplayObject.h>
#include <flash/core/Core.h>

namespace flash::display {
    class InteractiveObject : public DisplayObject {
        public:
            InteractiveObject();
           ~InteractiveObject() override;
    };
}

#endif
