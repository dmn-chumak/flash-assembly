#ifndef FLASH_EVENTS_ACTIVITY_EVENT_H
#define FLASH_EVENTS_ACTIVITY_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class ActivityEvent : public Event {
        public:
            static const sByte *ACTIVITY;

        public:
            bool activating;

        public:
            ActivityEvent(const String &type, bool bubbles = false, bool cancelable = false, bool activating = false);
           ~ActivityEvent() override;
    };
}

#endif
