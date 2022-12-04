#ifndef SHOOTER_LOCAL_MULTI_LOADER_EVENT_H
#define SHOOTER_LOCAL_MULTI_LOADER_EVENT_H

#include <flash/events/Event.h>
#include <flash/core/Core.h>
#include <flash/display/BitmapData.h>
#include <flash/utils/ByteArray.h>

using flash::display::BitmapData;
using flash::events::Event;
using flash::utils::ByteArray;

namespace shooter::local {
    class MultiLoaderEvent : public Event {
        public:
            Pointer<Array<BitmapData>> images;
            Pointer<Array<ByteArray>> bytes;
            MultiLoaderEvent();
            MultiLoaderEvent *MultiLoaderEventConstruct(String type, Pointer<Array<BitmapData>> images, Pointer<Array<ByteArray>> bytes);
            virtual ~MultiLoaderEvent() override;
    };
}

#endif

