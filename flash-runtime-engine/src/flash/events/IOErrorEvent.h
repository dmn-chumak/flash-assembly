#ifndef FLASH_EVENTS_IO_ERROR_EVENT_H
#define FLASH_EVENTS_IO_ERROR_EVENT_H

#include <flash/events/ErrorEvent.h>
#include <flash/core/Core.h>

namespace flash::events {
    class IOErrorEvent : public ErrorEvent {
        public:
            static const sByte *IO_ERROR;

        public:
            IOErrorEvent(const String &type, bool bubbles = false, bool cancelable = false, const String &text = nullptr, sInt errorID = 0);
           ~IOErrorEvent() override;
    };
}

#endif
