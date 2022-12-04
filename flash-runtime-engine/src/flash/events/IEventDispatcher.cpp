#include <flash/events/IEventDispatcher.h>

namespace flash::events {
    void IEventDispatcher::addEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture, sInt priority, bool weakReferences) {
        // empty
    }

    bool IEventDispatcher::dispatchEvent(const Pointer<Event> &event) {
        return false;
    }

    bool IEventDispatcher::hasEventListener(const String &type) {
        return false;
    }

    void IEventDispatcher::removeEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture) {
        // empty
    }

    bool IEventDispatcher::willTrigger(const String &type) {
        return false;
    }

    IEventDispatcher::~IEventDispatcher() {
        // empty
    }
}
