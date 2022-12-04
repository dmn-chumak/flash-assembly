#ifndef FLASH_EVENTS_SECURITY_ERROR_EVENT_H
#define FLASH_EVENTS_SECURITY_ERROR_EVENT_H

#include <flash/events/ErrorEvent.h>
#include <flash/core/Core.h>

namespace flash::events {
    class SecurityErrorEvent : public ErrorEvent {
        public:
            static const sByte *SECURITY_ERROR;

        public:
            SecurityErrorEvent(const String &type, bool bubbles = false, bool cancelable = false, const String &text = nullptr, sInt errorID = 0);
           ~SecurityErrorEvent() override;
    };
}

#endif
