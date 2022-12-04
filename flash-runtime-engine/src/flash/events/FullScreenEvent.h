#ifndef FLASH_EVENTS_FULL_SCREEN_EVENT_H
#define FLASH_EVENTS_FULL_SCREEN_EVENT_H

#include <flash/events/ActivityEvent.h>
#include <flash/core/Core.h>

namespace flash::events {
    class FullScreenEvent : public ActivityEvent {
        public:
            static const sByte *FULL_SCREEN;
            static const sByte *FULL_SCREEN_INTERACTIVE_ACCEPTED;

        public:
            bool fullScreen;
            bool interactive;

        public:
            FullScreenEvent(const String &type, bool bubbles = false, bool cancelable = false, bool fullScreen = false, bool interactive = false);
           ~FullScreenEvent() override;
    };
}

#endif
