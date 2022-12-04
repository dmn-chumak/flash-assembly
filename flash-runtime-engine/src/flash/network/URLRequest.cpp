#include <flash/network/URLRequest.h>
#include <flash/system/Console.h>

namespace flash::network {
    URLRequest::URLRequest(const String &url) {
        this->url = url;
    }

    URLRequest::~URLRequest() {
        // empty
    }
}