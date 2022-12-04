#ifndef FLASH_GEOMETRY_MATRIX_H
#define FLASH_GEOMETRY_MATRIX_H

#include <flash/geometry/Point.h>
#include <flash/geometry/Rectangle.h>
#include <flash/geometry/Vector3D.h>
#include <flash/core/Core.h>

namespace flash::geometry {
    class Matrix : public Object {
        public:
            float a;
            float b;
            float c;
            float d;
            float tx;
            float ty;

        public:
            Matrix(float a = 1, float b = 0, float c = 0, float d = 1, float tx = 0, float ty = 0);
           ~Matrix() override;

        public:
            Pointer<Matrix> clone() const;
            void concat(const Pointer<Matrix> &matrix);
            void copyColumnFrom(const uInt column, const Pointer<Vector3D> &vector);
            void copyColumnTo(const uInt column, Pointer<Vector3D> &vector) const;
            void copyFrom(const Pointer<Matrix> &matrix);
            void copyRowFrom(const uInt row, const Pointer<Vector3D> &vector);
            void copyRowTo(const uInt row, Pointer<Vector3D> &vector) const;
            Pointer<Point> deltaTransformPoint(const Pointer<Point> &point) const;
            bool equals(const Pointer<Matrix> &matrix) const;
            void identity();
            void invert();
            void rotate(const float angle);
            void scale(const float scaleX, const float scaleY);
            void setTo(const float newA, const float newB, const float newC, const float newD, const float newTx, const float newTy);
            Pointer<Point> transformPoint(const Pointer<Point> &point) const;
            void translate(const float deltaX, const float deltaY);
    };
}

#endif
