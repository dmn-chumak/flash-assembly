#include <flash/geometry/Utils3D.h>

namespace flash::geometry {
    Pointer<Vector3D> Utils3D::projectVector(Pointer<Matrix3D> &matrix, const Pointer<Vector3D> &vector) {
        Pointer<Vector<float>> &rawData = matrix->rawData;
        Pointer<Vector3D> project = new Vector3D();

        project->x = vector->x * rawData->obtainAt(0) + vector->y * rawData->obtainAt(4) + vector->z * rawData->obtainAt(8) + rawData->obtainAt(12);
        project->y = vector->x * rawData->obtainAt(1) + vector->y * rawData->obtainAt(5) + vector->z * rawData->obtainAt(9) + rawData->obtainAt(13);
        project->z = vector->x * rawData->obtainAt(2) + vector->y * rawData->obtainAt(6) + vector->z * rawData->obtainAt(10) + rawData->obtainAt(14);
        float w = vector->x * rawData->obtainAt(3) + vector->y * rawData->obtainAt(7) + vector->z * rawData->obtainAt(11) + rawData->obtainAt(15);

        project->z /= w;
        project->x /= w;
        project->y /= w;

        return project;
    }
}
