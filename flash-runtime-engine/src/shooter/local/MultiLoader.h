#ifndef SHOOTER_LOCAL_MULTI_LOADER_H
#define SHOOTER_LOCAL_MULTI_LOADER_H

#include <flash/display/BitmapData.h>
#include <flash/utils/ByteArray.h>
#include <flash/events/Event.h>
#include <flash/events/EventDispatcher.h>
#include <flash/network/URLLoader.h>
#include <flash/network/URLLoaderDataFormat.h>
#include <flash/network/URLRequest.h>
#include <flash/core/Core.h>
#include <shooter/local/MultiLoaderEvent.h>
#include <shooter/local/MultiLoaderAction.h>

using flash::events::Event;
using flash::events::EventDispatcher;
using flash::network::URLLoader;
using flash::network::URLLoaderDataFormat;
using flash::network::URLRequest;
using flash::display::BitmapData;
using flash::utils::ByteArray;

namespace shooter::local {
    class MultiLoader : public EventDispatcher {
        private:
            Pointer<Array<BitmapData>> _loadedImages;
            Pointer<Array<ByteArray>> _loadedBytes;
            Pointer<Array<MultiLoaderAction>> _actions;
            Pointer<URLLoader> _urlLoader;
            Pointer<URLLoader> _imgLoader;
            void urlLoaderCompleteHandler(const Pointer<Event> &event);
            void imgLoaderCompleteHandler(const Pointer<Event> &event);
            void loadNext();
        public:
            MultiLoader();
            MultiLoader *MultiLoaderConstruct();
            void load(Pointer<Array<MultiLoaderAction>> actions);
            virtual ~MultiLoader() override;
    };
}

#endif

