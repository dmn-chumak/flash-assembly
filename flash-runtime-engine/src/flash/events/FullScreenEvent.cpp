#include <flash/events/FullScreenEvent.h>

namespace flash::events {
    const sByte *FullScreenEvent::FULL_SCREEN = "fullScreen";
    const sByte *FullScreenEvent::FULL_SCREEN_INTERACTIVE_ACCEPTED = "fullScreenInteractiveAccepted";

    FullScreenEvent::FullScreenEvent(const String &type, bool bubbles, bool cancelable, bool fullScreen, bool interactive)
    : ActivityEvent(type, bubbles, cancelable, fullScreen)
    , fullScreen(fullScreen)
    , interactive(interactive) {
        // empty
    }

    FullScreenEvent::~FullScreenEvent() {
        // empty
    }
}
