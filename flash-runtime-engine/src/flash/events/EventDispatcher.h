#ifndef FLASH_EVENTS_EVENT_DISPATCHER_H
#define FLASH_EVENTS_EVENT_DISPATCHER_H

#include <flash/events/IEventDispatcher.h>
#include <flash/core/Core.h>

namespace flash::events {
    class EventDispatcher : public Object, public IEventDispatcher {
        private:
            HashMap<String, Array<EventListener>> _listeners;

        public:
            EventDispatcher();
           ~EventDispatcher() override;

        public:
            void addEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture = false, sInt priority = 0, bool weakReferences = false) override;
            bool dispatchEvent(const Pointer<Event> &event) override;
            bool hasEventListener(const String &type) override;
            void removeEventListener(const String &type, const Pointer<EventListener> &listener, bool usCapture = false) override;
            bool willTrigger(const String &type) override;

        private:
            Pointer<Array<EventListener>> obtainListeners(const String &type, const bool create = false);
    };
}

#endif
