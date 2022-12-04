#ifndef FLASH_EVENTS_FOCUS_EVENT_H
#define FLASH_EVENTS_FOCUS_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class FocusEvent : public Event {
        public:
            static const sByte  *FOCUS_IN;
            static const sByte  *FOCUS_OUT;

        public:
            uInt keyCode;
            Pointer<Object> relatedObject;
            bool shiftKey;

        public:
            FocusEvent(const String &type, bool bubbles = false, bool cancelable = false, bool activating = false);
           ~FocusEvent() override;
    };
}

#endif
