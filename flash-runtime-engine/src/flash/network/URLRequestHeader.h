#ifndef FLASH_NETWORK_URL_REQUEST_HEADER_H
#define FLASH_NETWORK_URL_REQUEST_HEADER_H

#include <flash/core/Core.h>

namespace flash::network {
    class URLRequestHeader final : public Object {
        public:
            String value;
            String name;

        public:
            URLRequestHeader(const String &name = "", const String &value = "");
           ~URLRequestHeader() override;
    };
}

#endif
