#ifndef FLASH_GEOMETRY_MATRIX_3D_H
#define FLASH_GEOMETRY_MATRIX_3D_H

#include <flash/geometry/Vector3D.h>
#include <flash/core/Core.h>

namespace flash::geometry {
    class Matrix3D : public Object {
        public:
            Pointer<Vector<float>> rawData;

        public:
            Matrix3D(const Pointer<Vector<float>> &source = nullptr);
           ~Matrix3D() override;

        public:
            static Pointer<Matrix3D> interpolate(const Pointer<Matrix3D> &firstMatrix, const Pointer<Matrix3D> &secondMatrix, const float percent);

        public:
            void append(const Pointer<Matrix3D> &matrix);
            void appendRotation(const float angle, const Pointer<Vector3D> &axis, const Pointer<Vector3D> pivot = nullptr);
            void appendScale(const float scaleX, const float scaleY, const float scaleZ);
            void appendTranslation(const float deltaX, const float deltaY, const float deltaZ);
            Pointer<Matrix3D> clone() const;
            void copyColumnFrom(const uInt column, const Pointer<Vector3D> &vector);
            void copyColumnTo(const uInt column, Pointer<Vector3D> &vector) const;
            void copyFrom(const Pointer<Matrix3D> &matrix);
            void copyRawDataFrom(const Pointer<Vector<float>> &vector, uInt index = 0, bool needTranspose = false);
            void copyRawDataTo(Pointer<Vector<float>> &vector, uInt index = 0, bool needTranspose = false);
            void copyRowFrom(const uInt row, const Pointer<Vector3D> &vector);
            void copyRowTo(const uInt row, Pointer<Vector3D> &vector) const;
            void copyToMatrix(Pointer<Matrix3D> &matrix) const;
            Pointer<Array<Vector3D>> decompose(String &orientationStyle);
            Pointer<Vector3D> deltaTransformVector(const Pointer<Vector3D> &vector);
            void identity();
            void interpolateTo(const Pointer<Matrix3D> &matrix, const float percent);
            bool invert();
            void pointAt(const Pointer<Vector3D> &vector, const Pointer<Vector3D> &at = nullptr, const Pointer<Vector3D> &up = nullptr);
            void prepend(const Pointer<Matrix3D> &matrix);
            void prependRotation(const float angle, const Pointer<Vector3D> &axis, const Pointer<Vector3D> pivot = nullptr);
            void prependScale(const float scaleX, const float scaleY, const float scaleZ);
            void prependTranslation(const float deltaX, const float deltaY, const float deltaZ);
            bool recompose(Pointer<Array<Vector3D>> components, String &orientationStyle);
            Pointer<Vector3D> transformVector(const Pointer<Vector3D> &vector);
            void transformVectors();
            void transpose();

        public:
            float determinant() const;
            void setPosition(Pointer<Vector3D> vector);
            Pointer<Vector3D> getPosition();
    };
}

#endif
