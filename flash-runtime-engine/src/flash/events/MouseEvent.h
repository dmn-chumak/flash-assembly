#ifndef FLASH_EVENTS_MOUSE_EVENT_H
#define FLASH_EVENTS_MOUSE_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    class MouseEvent : public Event {
        public:
            static const sByte *CLICK;
            static const sByte *DOUBLE_CLICK;
            static const sByte *MIDDLE_CLICK;
            static const sByte *MIDDLE_MOUSE_DOWN;
            static const sByte *MIDDLE_MOUSE_UP;
            static const sByte *MOUSE_DOWN;
            static const sByte *MOUSE_MOVE;
            static const sByte *MOUSE_OUT;
            static const sByte *MOUSE_OVER;
            static const sByte *MOUSE_UP;
            static const sByte *MOUSE_WHEEL;
            static const sByte *RELEASE_OUTSIDE;
            static const sByte *RIGHT_CLICK;
            static const sByte *RIGHT_MOUSE_DOWN;
            static const sByte *RIGHT_MOUSE_UP;
            static const sByte *ROLL_OUT;
            static const sByte *ROLL_OVER;

        public:
            bool altKey;
            bool buttonDown;
            sInt clickCount;
            bool commandKey;
            bool controlKey;
            bool ctrlKey;
            sInt delta;
            double localX;
            double localY;
            double movementX;
            double movementY;
            Pointer<Object> relatedObject;
            bool shiftKey;
            double stageX;
            double stageY;

        public:
            MouseEvent(const String &type, bool bubbles = false, bool cancelable = false);
           ~MouseEvent() override;
    };
}

#endif
