#ifndef FLASH_EVENTS_KEYBOARD_EVENT_H
#define FLASH_EVENTS_KEYBOARD_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class KeyboardEvent : public Event {
        public:
            static const sByte *KEY_DOWN;
            static const sByte *KEY_UP;

        public:
            bool altKey;
            uInt charCode;
            bool commandKey;
            bool ctrlKey;
            uInt keyCode;
            uInt keyLocation;
            bool shiftKey;

        public:
            KeyboardEvent(const String &type, bool bubbles = false, bool cancelable = false);
           ~KeyboardEvent() override;
    };
}

#endif
