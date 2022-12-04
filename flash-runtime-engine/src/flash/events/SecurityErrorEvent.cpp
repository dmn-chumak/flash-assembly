#include <flash/events/SecurityErrorEvent.h>

namespace flash::events {
    const sByte *SecurityErrorEvent::SECURITY_ERROR = "securityError";

    SecurityErrorEvent::SecurityErrorEvent(const String &type, bool bubbles, bool cancelable, const String &text, sInt errorID)
    : ErrorEvent(type, bubbles, cancelable, text, errorID) {
        // empty
    }

    SecurityErrorEvent::~SecurityErrorEvent() {
        // empty
    }
}
