#include <flash/events/ProgressEvent.h>

namespace flash::events {
    const sByte *ProgressEvent::PROGRESS = "progress";
    const sByte *ProgressEvent::SOCKET_DATA = "socketData";

    ProgressEvent::ProgressEvent(const String &type, bool bubbles, bool cancelable, heap bytesLoaded, heap bytesTotal)
    : Event(type, bubbles, cancelable)
    , bytesLoaded(bytesLoaded)
    , bytesTotal(bytesTotal) {
        // empty
    }

    ProgressEvent::~ProgressEvent() {
        // empty
    }
}
