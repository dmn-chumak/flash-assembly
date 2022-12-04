#include <flash/events/HTTPStatusEvent.h>

namespace flash::events {
    const sByte *HTTPStatusEvent::HTTP_STATUS = "httpStatus";

    HTTPStatusEvent::HTTPStatusEvent(const String &type, bool bubbles, bool cancelable, sInt status, bool redirected)
    : Event(type, bubbles, cancelable)
    , status(status)
    , redirected(redirected) {
        // empty
    }

    HTTPStatusEvent::~HTTPStatusEvent() {
        // empty
    }
}
