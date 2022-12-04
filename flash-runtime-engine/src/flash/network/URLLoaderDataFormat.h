#ifndef FLASH_NETWORK_URL_LOADER_DATA_FORMAT_H
#define FLASH_NETWORK_URL_LOADER_DATA_FORMAT_H

#include <flash/core/Core.h>

namespace flash::network {
    class URLLoaderDataFormat final {
        public:
            static const sByte *BINARY;
            static const sByte *TEXT;
            static const sByte *VARIABLES;
    };
}

#endif
