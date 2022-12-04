#ifndef FLASH_EVENTS_I_EVENT_DISPATCHER_H
#define FLASH_EVENTS_I_EVENT_DISPATCHER_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>

namespace flash::events {
    typedef Function<void, const Pointer<Event> &> EventListener;

    class IEventDispatcher {
        public:
            virtual void addEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture = false, sInt priority = 0, bool weakReferences = false);
            virtual bool dispatchEvent(const Pointer<Event> &event);
            virtual bool hasEventListener(const String &type);
            virtual void removeEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture = false);
            virtual bool willTrigger(const String &type);
            virtual ~IEventDispatcher();
    };
}

#endif
