#ifndef FLASH_EVENTS_EVENT_PHASE_H
#define FLASH_EVENTS_EVENT_PHASE_H

#include <flash/core/Core.h>

namespace flash::events {
    class EventPhase final {
        public:
            static const uInt CAPTURING_PHASE;
            static const uInt AT_TARGET;
            static const uInt BUBBLING_PHASE;
    };
}

#endif
