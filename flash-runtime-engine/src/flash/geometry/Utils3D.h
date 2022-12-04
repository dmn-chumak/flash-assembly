#ifndef FLASH_GEOMETRY_UTILS_3D_H
#define FLASH_GEOMETRY_UTILS_3D_H

#include <flash/geometry/Matrix3D.h>
#include <flash/geometry/Vector3D.h>
#include <flash/core/Core.h>

namespace flash::geometry {
    class Utils3D final {
        public:
            // TODO: static Pointer<Matrix3D> pointTowards(const float percent, const Pointer<Matrix3D> &matrix, const Pointer<Vector3D> &pos, const Pointer<Vector3D> &at = nullptr, const Pointer<Vector3D> &up = nullptr);
            static Pointer<Vector3D> projectVector(Pointer<Matrix3D> &matrix, const Pointer<Vector3D> &vector);
            // TODO: static void projectVectors(const Pointer<Matrix3D> &matrix, const Pointer<Array<Double>> &verts, const Pointer<Array<Double>> &projectedVerts, const Pointer<Array<Double>> &uvts);
    };
}

#endif
