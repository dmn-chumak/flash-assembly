#include <flash/events/IOErrorEvent.h>

namespace flash::events {
    const sByte *IOErrorEvent::IO_ERROR = "ioError";

    IOErrorEvent::IOErrorEvent(const String &type, bool bubbles, bool cancelable, const String &text, sInt errorID)
    : ErrorEvent(type, bubbles, cancelable, text, errorID) {
        // empty
    }

    IOErrorEvent::~IOErrorEvent() {
        // empty
    }
}
