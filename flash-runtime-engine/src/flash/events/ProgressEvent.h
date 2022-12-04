#ifndef FLASH_EVENTS_PROGRESS_EVENT_H
#define FLASH_EVENTS_PROGRESS_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class ProgressEvent : public Event {
        public:
            static const sByte *PROGRESS;
            static const sByte *SOCKET_DATA;

        public:
            heap bytesLoaded;
            heap bytesTotal;

        public:
            ProgressEvent(const String &type, bool bubbles = false, bool cancelable = false, heap bytesLoaded = 0, heap bytesTotal = 0);
           ~ProgressEvent() override;
    };
}

#endif
