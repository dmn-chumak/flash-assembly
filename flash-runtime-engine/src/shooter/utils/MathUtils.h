#ifndef SHOOTER_UTILS_MATH_UTILS_H
#define SHOOTER_UTILS_MATH_UTILS_H

#include <flash/core/Core.h>

namespace shooter::utils {
    class MathUtils : public Object {
        private:
        protected:
        public:
            static sInt nextPowerOfTwo(sInt source);
    };
}

#endif

