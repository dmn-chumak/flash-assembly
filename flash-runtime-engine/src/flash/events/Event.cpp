#include <flash/events/Event.h>
#include <flash/events/EventPhase.h>

namespace flash::events {
    const sByte *Event::ACTIVATE = "activate";
    const sByte *Event::ADDED = "added";
    const sByte *Event::ADDED_TO_STAGE = "addedToStage";
    const sByte *Event::CANCEL = "cancel";
    const sByte *Event::CHANGE = "change";
    const sByte *Event::CHANNEL_MESSAGE = "channelMessage";
    const sByte *Event::CHANNEL_STATE = "channelState";
    const sByte *Event::CLEAR = "clear";
    const sByte *Event::CLOSE = "close";
    const sByte *Event::COMPLETE = "complete";
    const sByte *Event::CONNECT = "connect";
    const sByte *Event::CONTEXT3D_CREATE = "context3DCreate";
    const sByte *Event::COPY = "copy";
    const sByte *Event::CUT = "cut";
    const sByte *Event::DEACTIVATE = "deactivate";
    const sByte *Event::ENTER_FRAME = "enterFrame";
    const sByte *Event::EXIT_FRAME = "exitFrame";
    const sByte *Event::FRAME_CONSTRUCTED = "frameConstructed";
    const sByte *Event::FULLSCREEN = "fullScreen";
    const sByte *Event::INIT = "init";
    const sByte *Event::MOUSE_LEAVE = "mouseLeave";
    const sByte *Event::OPEN = "open";
    const sByte *Event::PASTE = "paste";
    const sByte *Event::REMOVED = "removed";
    const sByte *Event::REMOVED_FROM_STAGE = "removedFromStage";
    const sByte *Event::RENDER = "render";
    const sByte *Event::RESIZE = "resize";
    const sByte *Event::SCROLL = "scroll";
    const sByte *Event::SELECT = "select";
    const sByte *Event::SELECT_ALL = "selectAll";
    const sByte *Event::SOUND_COMPLETE = "soundComplete";
    const sByte *Event::TEXTURE_READY = "textureReady";
    const sByte *Event::UNLOAD = "unload";

    Event::Event(const String &type, bool bubbles, bool cancelable)
    : type(type)
    , cancelable(cancelable)
    , bubbles(bubbles)
    , eventPhase(EventPhase::AT_TARGET) {
        // empty
    }

    Event::~Event() {
        // empty
    }

    Pointer<Event> Event::clone() const {
        Pointer<Event> event = new Event(type, bubbles, cancelable);

        event->eventPhase = eventPhase;
        event->target = target;
        event->currentTarget = currentTarget;

        return event;
    }

    bool Event::isDefaultPrevented() const {
        return _isDefaultPrevented;
    }

    void Event::preventDefault() {
        if (cancelable) {
            _isDefaultPrevented = true;
        }
    }

    void Event::stopImmediatePropagation() {
        _isCanceledNow = true;
        _isCanceled = true;
    }

    void Event::stopPropagation() {
        _isCanceled = true;
    }

    String Event::toString() const {
        return type;
    }
}
