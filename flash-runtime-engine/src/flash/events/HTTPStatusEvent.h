#ifndef FLASH_EVENTS_HTTP_STATUS_EVENT_H
#define FLASH_EVENTS_HTTP_STATUS_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class HTTPStatusEvent : public Event {
        public:
            static const sByte *HTTP_STATUS;

        public:
            bool redirected;
            sInt status;

        public:
            HTTPStatusEvent(const String &type, bool bubbles = false, bool cancelable = false, sInt status = 0, bool redirected = false);
           ~HTTPStatusEvent() override;
    };
}

#endif
