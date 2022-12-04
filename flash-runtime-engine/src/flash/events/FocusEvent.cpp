#include <flash/events/FocusEvent.h>

namespace flash::events {
    const sByte *FocusEvent::FOCUS_IN = "focusIn";
    const sByte *FocusEvent::FOCUS_OUT = "focusOut";

    FocusEvent::FocusEvent(const String &type, bool bubbles, bool cancelable, bool activating)
    : Event(type, bubbles, cancelable) {
        // empty
    }

    FocusEvent::~FocusEvent() {
        // empty
    }
}
