#include <flash/events/MouseEvent.h>

namespace flash::events {
    const sByte *MouseEvent::CLICK = "click";
    const sByte *MouseEvent::DOUBLE_CLICK = "doubleClick";
    const sByte *MouseEvent::MIDDLE_CLICK = "middleClick";
    const sByte *MouseEvent::MIDDLE_MOUSE_DOWN = "middleMouseDown";
    const sByte *MouseEvent::MIDDLE_MOUSE_UP = "middleMouseUp";
    const sByte *MouseEvent::MOUSE_DOWN = "mouseDown";
    const sByte *MouseEvent::MOUSE_MOVE = "mouseMove";
    const sByte *MouseEvent::MOUSE_OUT = "mouseOut";
    const sByte *MouseEvent::MOUSE_OVER = "mouseOver";
    const sByte *MouseEvent::MOUSE_UP = "mouseUp";
    const sByte *MouseEvent::MOUSE_WHEEL = "mouseWheel";
    const sByte *MouseEvent::RELEASE_OUTSIDE = "releaseOutside";
    const sByte *MouseEvent::RIGHT_CLICK = "rightClick";
    const sByte *MouseEvent::RIGHT_MOUSE_DOWN = "rightMouseDown";
    const sByte *MouseEvent::RIGHT_MOUSE_UP = "rightMouseUp";
    const sByte *MouseEvent::ROLL_OUT = "rollOut";
    const sByte *MouseEvent::ROLL_OVER = "rollOver";

    MouseEvent::MouseEvent(const String &type, bool bubbles, bool cancelable)
    : Event(type, bubbles, cancelable) {
        // empty
    }

    MouseEvent::~MouseEvent() {
        // empty
    }
}
