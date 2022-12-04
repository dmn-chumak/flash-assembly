#ifndef FLASH_EVENTS_TEXT_EVENT_H
#define FLASH_EVENTS_TEXT_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class TextEvent : public Event {
        public:
            static const sByte *LINK;
            static const sByte *TEXT_INPUT;

        public:
            String text;

        public:
            TextEvent(const String &type, bool bubbles = false, bool cancelable = false, const String &text = nullptr);
           ~TextEvent() override;
    };
}

#endif
