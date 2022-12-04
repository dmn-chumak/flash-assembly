#include <flash/events/ActivityEvent.h>

namespace flash::events {
    const sByte *ActivityEvent::ACTIVITY = "activity";

    ActivityEvent::ActivityEvent(const String &type, bool bubbles, bool cancelable, bool activating)
    : Event(type, bubbles, cancelable)
    , activating(activating) {
        // empty
    }

    ActivityEvent::~ActivityEvent() {
        // empty
    }
}
