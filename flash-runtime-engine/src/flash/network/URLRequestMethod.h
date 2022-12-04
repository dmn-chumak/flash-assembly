#ifndef FLASH_NETWORK_URL_REQUEST_METHOD_H
#define FLASH_NETWORK_URL_REQUEST_METHOD_H

#include <flash/core/Core.h>

namespace flash::network {
    class URLRequestMethod final {
        public:
            static const sByte *POST;
            static const sByte *GET;
    };
}

#endif
