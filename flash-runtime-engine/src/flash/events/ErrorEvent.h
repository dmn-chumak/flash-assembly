#ifndef FLASH_EVENTS_ERROR_EVENT_H
#define FLASH_EVENTS_ERROR_EVENT_H

#include <flash/events/TextEvent.h>
#include <flash/core/Core.h>

namespace flash::events {
    class ErrorEvent : public TextEvent {
        public:
            static const sByte *ERROR;

        public:
            sInt errorID;

        public:
            ErrorEvent(const String &type, bool bubbles = false, bool cancelable = false, const String &text = nullptr, sInt errorID = 0);
           ~ErrorEvent() override;
    };
}

#endif
