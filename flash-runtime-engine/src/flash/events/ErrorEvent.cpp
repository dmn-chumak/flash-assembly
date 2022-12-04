#include <flash/events/ErrorEvent.h>

namespace flash::events {
    const sByte *ErrorEvent::ERROR = "error";

    ErrorEvent::ErrorEvent(const String &type, bool bubbles, bool cancelable, const String &text, sInt errorID)
    : TextEvent(type, bubbles, cancelable, text)
    , errorID(errorID) {
        // empty
    }

    ErrorEvent::~ErrorEvent() {
        // empty
    }
}
