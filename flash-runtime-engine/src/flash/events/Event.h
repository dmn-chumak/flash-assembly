#ifndef FLASH_EVENTS_EVENT_H
#define FLASH_EVENTS_EVENT_H

#include <flash/core/Core.h>

namespace flash::events {
    class Event : public Object {
        public:
            static const sByte *ACTIVATE;
            static const sByte *ADDED;
            static const sByte *ADDED_TO_STAGE;
            static const sByte *CANCEL;
            static const sByte *CHANGE;
            static const sByte *CHANNEL_MESSAGE;
            static const sByte *CHANNEL_STATE;
            static const sByte *CLEAR;
            static const sByte *CLOSE;
            static const sByte *COMPLETE;
            static const sByte *CONNECT;
            static const sByte *CONTEXT3D_CREATE;
            static const sByte *COPY;
            static const sByte *CUT;
            static const sByte *DEACTIVATE;
            static const sByte *ENTER_FRAME;
            static const sByte *EXIT_FRAME;
            static const sByte *FRAME_CONSTRUCTED;
            static const sByte *FULLSCREEN;
            static const sByte *INIT;
            static const sByte *MOUSE_LEAVE;
            static const sByte *NETWORK_CHANGE;
            static const sByte *OPEN;
            static const sByte *PASTE;
            static const sByte *REMOVED;
            static const sByte *REMOVED_FROM_STAGE;
            static const sByte *RENDER;
            static const sByte *RESIZE;
            static const sByte *SCROLL;
            static const sByte *SELECT;
            static const sByte *SELECT_ALL;
            static const sByte *SOUND_COMPLETE;
            static const sByte *TEXTURE_READY;
            static const sByte *UNLOAD;

        protected:
            bool _isDefaultPrevented;
            bool _isCanceled;
            bool _isCanceledNow;

        public:
            bool bubbles;
            bool cancelable;
            Pointer<Object> currentTarget;
            uInt eventPhase;
            Pointer<Object> target;
            String type;

        public:
            Event(const String &type, bool bubbles = false, bool cancelable = false);
           ~Event() override;

        public:
            Pointer<Event> clone() const;
            bool isDefaultPrevented() const;
            void preventDefault();
            void stopImmediatePropagation();
            void stopPropagation();
            String toString() const override;
    };
}

#endif
