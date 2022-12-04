#include <flash/events/EventDispatcher.h>
#include <flash/events/EventPhase.h>

namespace flash::events {
    EventDispatcher::EventDispatcher() {
        // empty
    }

    EventDispatcher::~EventDispatcher() {
        // empty
    }

    void EventDispatcher::addEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture, sInt priority, bool weakReferences) {
        obtainListeners(type, true)->insertLast(listener);
    }

    bool EventDispatcher::dispatchEvent(const Pointer<Event> &event) {
        Pointer<Array<EventListener>> listeners = obtainListeners(event->type);
        Pointer<Event> realEvent = event;

        realEvent->eventPhase = EventPhase::CAPTURING_PHASE;
        realEvent->currentTarget = this;
        realEvent->target = this;

        if (listeners != nullptr
        &&  listeners->length() > 0) {
            for (heap index = 0; index < listeners->length(); ++index) {
                listeners->obtainAt(index)->call(realEvent);
            }

            return true;
        }

        return false;
    }

    bool EventDispatcher::hasEventListener(const String &type) {
        Pointer<Array<EventListener>> listeners = obtainListeners(type);

        if (listeners != nullptr
        &&  listeners->length() > 0) {
            return true;
        }

        return false;
    }

    void EventDispatcher::removeEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture) {
        Pointer<Array<EventListener>> listeners = obtainListeners(type);

        if (listeners != nullptr) {
            const sInt index = listeners->indexOf(listener);
            if (index != INVALID_INDEX) {
                listeners->removeAt(static_cast<const heap>(index));
            }
        }
    }

    bool EventDispatcher::willTrigger(const String &type) {
        // TODO: add correct implementation with difference
        return hasEventListener(type);
    }

    Pointer<Array<EventListener>> EventDispatcher::obtainListeners(const String &type, const bool create) {
        // TODO: fix reallocating memory for string keys
        Pointer<Array<EventListener>> listeners = _listeners.obtainByKey(new String(type));

        if (listeners == nullptr && create) {
            _listeners.insertByKey(
                new String(type), listeners = new Array<EventListener>()
            );
        }

        return listeners;
    }
}