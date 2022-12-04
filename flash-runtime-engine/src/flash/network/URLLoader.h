#ifndef FLASH_NETWORK_URL_LOADER_H
#define FLASH_NETWORK_URL_LOADER_H

#include <flash/events/EventDispatcher.h>
#include <flash/network/URLRequest.h>
#include <flash/core/Core.h>

namespace flash::network {
    class URLLoader : public events::EventDispatcher {
        private:
            static const sInt INTERNAL_HTTP_STATUS_EVENT;
            static const sInt INTERNAL_OPEN_EVENT;
            static const sInt INTERNAL_IO_ERROR_EVENT;
            static const sInt INTERNAL_COMPLETE_EVENT;
            static const sInt INTERNAL_PROGRESS_EVENT;
            static const sInt INTERNAL_SECURITY_ERROR_EVENT;

        private:
            bool _isLoading;
            Pointer<URLRequest> _request;
            sInt _loaderID;

        public:
            heap bytesLoaded;
            heap bytesTotal;
            Pointer<Object> data;
            String dataFormat;

        private:
            static void globalEventCallback(URLLoader *loader, sInt event = 0, heap first = 0, heap second = 0);
            void localEventCallback(sInt event = 0, heap first = 0, heap second = 0);

        public:
            URLLoader(const Pointer<URLRequest> &request = nullptr);
           ~URLLoader() override;

        public:
            void load(const Pointer<URLRequest> &request);
            void close();
    };
}

#endif
