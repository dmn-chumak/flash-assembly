#include <flash/network/URLRequestHeader.h>

namespace flash::network {
    URLRequestHeader::URLRequestHeader(const String &name, const String &value)
    : value(value), name(name) {
        // empty
    }

    URLRequestHeader::~URLRequestHeader() {
        // empty
    }
}
