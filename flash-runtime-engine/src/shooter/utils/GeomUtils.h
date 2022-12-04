#ifndef SHOOTER_UTILS_GEOM_UTILS_H
#define SHOOTER_UTILS_GEOM_UTILS_H

#include <flash/geometry/Matrix.h>
#include <flash/core/Core.h>

using flash::geometry::Matrix;

namespace shooter::utils {
    class GeomUtils : public Object {
        private:
        protected:
        public:
            static void concat(Pointer<Matrix> base, Pointer<Matrix> from, Pointer<Matrix> prep);
            static bool identity(Pointer<Matrix> matrix);
    };
}

#endif

