#include <flash/events/KeyboardEvent.h>

namespace flash::events {
    const sByte *KeyboardEvent::KEY_DOWN = "keyDown";
    const sByte *KeyboardEvent::KEY_UP = "keyUp";

    KeyboardEvent::KeyboardEvent(const String &type, bool bubbles, bool cancelable)
    : Event(type, bubbles, cancelable) {
        // empty
    }

    KeyboardEvent::~KeyboardEvent() {
        // empty
    }
}
