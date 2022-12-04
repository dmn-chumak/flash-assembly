#include <shooter/utils/MathUtils.h>

namespace shooter::utils {
    sInt MathUtils::nextPowerOfTwo(sInt source) {
        sInt value = 0;
        value = sInt(1);
        while (value < source) {
            value <<= sInt(1);
        }
        return value;
    }

}

