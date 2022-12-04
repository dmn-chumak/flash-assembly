#ifndef FLASH_NETWORK_URL_VARIABLES_H
#define FLASH_NETWORK_URL_VARIABLES_H

#include <flash/core/Core.h>

namespace flash::network {
    class URLVariables final : public HashMap<String, Object> {
        public:
            URLVariables(const String &source = nullptr);
           ~URLVariables() override;
    };
}

#endif
