#ifndef FLASH_NETWORK_URL_REQUEST_H
#define FLASH_NETWORK_URL_REQUEST_H

#include <flash/network/URLVariables.h>
#include <flash/network/URLRequestHeader.h>
#include <flash/core/Core.h>

namespace flash::network {
    class URLRequest final : public Object {
        public:
            String contentType;
            Pointer<URLVariables> data;
            String digest;
            String method;
            Array<URLRequestHeader> requestHeaders;
            String url;

        public:
            URLRequest(const String &url = nullptr);
           ~URLRequest() override;
    };
}

#endif
