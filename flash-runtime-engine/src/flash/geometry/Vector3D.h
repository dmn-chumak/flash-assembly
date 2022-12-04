#ifndef FLASH_GEOMETRY_VECTOR_3D_H
#define FLASH_GEOMETRY_VECTOR_3D_H

#include <flash/core/Core.h>

namespace flash::geometry {
    class Vector3D final : public Object {
        public:
            float x;
            float y;
            float z;
            float w;

        public:
            Vector3D(const float x = 0, const float y = 0, const float z = 0, const float w = 0);
           ~Vector3D() override;

        public:
            static float angleBetween(const Pointer<Vector3D> &firstVector, const Pointer<Vector3D> &secondVector);
            static float distance(const Pointer<Vector3D> &firstVector, const Pointer<Vector3D> &secondVector);

            Pointer<Vector3D> add(const Pointer<Vector3D> &vector) const;
            Pointer<Vector3D> clone() const;
            void copyFrom(const Pointer<Vector3D> &vector);
            Pointer<Vector3D> crossProduct(const Pointer<Vector3D> &vector) const;
            void decrementBy(const Pointer<Vector3D> &vector);
            float dotProduct(const Pointer<Vector3D> &vector) const;
            bool equals(const Pointer<Vector3D> &vector, const bool everything = false) const;
            void incrementBy(const Pointer<Vector3D> &vector);
            bool nearEquals(const Pointer<Vector3D> &vector, const float tolerance, const bool everything = false);
            void negate();
            float normalize();
            void project();
            void scaleBy(const float scale);
            void setTo(const float newX, const float newY, const float newZ);
            Pointer<Vector3D> subtract(const Pointer<Vector3D> &vector) const;

        public:
            float lengthSquared() const;
            float length() const;
    };
}

#endif
