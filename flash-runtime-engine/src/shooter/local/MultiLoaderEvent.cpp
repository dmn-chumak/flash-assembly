#include <shooter/local/MultiLoaderEvent.h>

namespace shooter::local {
    MultiLoaderEvent::MultiLoaderEvent() : Event(Event::COMPLETE) {
        images = nullptr;
        bytes = nullptr;
    }

    MultiLoaderEvent *MultiLoaderEvent::MultiLoaderEventConstruct(String type, Pointer<Array<BitmapData>> images, Pointer<Array<ByteArray>> bytes) {
        this->type = type;
        this->images = images;
        this->bytes = bytes;
        return this;
    }

    MultiLoaderEvent::~MultiLoaderEvent() {
    }
}

