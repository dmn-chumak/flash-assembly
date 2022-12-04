#ifndef FLASH_GEOMETRY_ORIENTATION_3D_H
#define FLASH_GEOMETRY_ORIENTATION_3D_H

#include <flash/core/Core.h>

namespace flash::geometry {
    class Orientation3D final {
        public:
            static const sByte *AXIS_ANGLE;
            static const sByte *EULER_ANGLES;
            static const sByte *QUATERNION;
    };
}

#endif
