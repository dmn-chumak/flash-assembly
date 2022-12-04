#include <flash/geometry/Vector3D.h>
#include <flash/utils/Math.h>

namespace flash::geometry {
    Vector3D::Vector3D(const float x, const float y, const float z, const float w)
    : x(x), y(y), z(z), w(w) {
        // empty
    }

    Vector3D::~Vector3D() {
        // empty
    }

    float Vector3D::angleBetween(const Pointer<Vector3D> &firstVector, const Pointer<Vector3D> &secondVector) {
        float la = firstVector->length();
        float lb = secondVector->length();
        float dot = firstVector->dotProduct(secondVector);

        if (la != 0) {
            dot /= la;
        }

        if (lb != 0) {
            dot /= lb;
        }

        return (float)utils::Math::acos(dot);
    }

    float Vector3D::distance(const Pointer<Vector3D> &firstVector, const Pointer<Vector3D> &secondVector) {
        float x = secondVector->x - firstVector->x;
        float y = secondVector->y - firstVector->y;
        float z = secondVector->z - firstVector->z;

        return (float)utils::Math::sqrt(x * x + y * y + z * z);
    }

    Pointer<Vector3D> Vector3D::add(const Pointer<Vector3D> &vector) const {
        return new Vector3D(
            x + vector->x,
            y + vector->y,
            z + vector->z
        );
    }

    Pointer<Vector3D> Vector3D::clone() const {
        return new Vector3D(x, y, z, w);
    }

    void Vector3D::copyFrom(const Pointer<Vector3D> &vector) {
        x = vector->x;
        y = vector->y;
        z = vector->z;
    }

    Pointer<Vector3D> Vector3D::crossProduct(const Pointer<Vector3D> &vector) const {
        return new Vector3D(
            y * vector->z - z * vector->y,
            z * vector->x - x * vector->z,
            x * vector->y - y * vector->x,
            1
        );
    }

    void Vector3D::decrementBy(const Pointer<Vector3D> &vector) {
        x -= vector->x;
        y -= vector->y;
        z -= vector->z;
    }

    float Vector3D::dotProduct(const Pointer<Vector3D> &vector) const {
        return x * vector->x + y * vector->y + z * vector->z;
    }

    bool Vector3D::equals(const Pointer<Vector3D> &vector, const bool everything) const {
        return (
               x == vector->x
            && y == vector->y
            && z == vector->z
            && (!everything || w == vector->w)
        );
    }

    void Vector3D::incrementBy(const Pointer<Vector3D> &vector) {
        x += vector->x;
        y += vector->y;
        z += vector->z;
    }

    bool Vector3D::nearEquals(const Pointer<Vector3D> &vector, const float tolerance, const bool everything) {
        return (
               utils::Math::abs(x - vector->x) < tolerance
            && utils::Math::abs(y - vector->y) < tolerance
            && utils::Math::abs(z - vector->z) < tolerance
            && (!everything || utils::Math::abs(w - vector->w) < tolerance)
        );
    }

    void Vector3D::negate() {
        x *= -1;
        y *= -1;
        z *= -1;
    }

    float Vector3D::normalize() {
        float norm = length();

        if (norm != 0) {
            x /= norm;
            y /= norm;
            z /= norm;
        }

        return norm;
    }

    void Vector3D::project() {
        x /= w;
        y /= w;
        z /= w;
    }

    void Vector3D::scaleBy(const float scale) {
        x *= scale;
        y *= scale;
        z *= scale;
    }

    void Vector3D::setTo(const float newX, const float newY, const float newZ) {
        x = newX;
        y = newY;
        z = newZ;
    }

    Pointer<Vector3D> Vector3D::subtract(const Pointer<Vector3D> &vector) const {
        return new Vector3D(
            x - vector->x,
            y - vector->y,
            z - vector->z
        );
    }

    float Vector3D::lengthSquared() const {
        return x * x + y * y + z * z;
    }

    float Vector3D::length() const {
        return (float)utils::Math::sqrt(x * x + y * y + z * z);
    }
}
