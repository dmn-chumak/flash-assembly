#include <flash/events/TextEvent.h>

namespace flash::events {
    const sByte *TextEvent::LINK = "link";
    const sByte *TextEvent::TEXT_INPUT = "textInput";

    TextEvent::TextEvent(const String &type, bool bubbles, bool cancelable, const String &text)
    : Event(type, bubbles, cancelable)
    , text(text) {
        // empty
    }

    TextEvent::~TextEvent() {
        // empty
    }
}
