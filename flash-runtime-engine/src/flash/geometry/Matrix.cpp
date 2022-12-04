#include <flash/geometry/Matrix.h>
#include <flash/utils/Math.h>

namespace flash::geometry {
    Matrix::Matrix(float a, float b, float c, float d, float tx, float ty)
    : a(a), b(b), c(c), d(d), tx(tx), ty(ty) {
        // empty
    }

    Matrix::~Matrix() {
        // empty
    }

    Pointer<Matrix> Matrix::clone() const {
        return new Matrix(a, b, c, d, tx, ty);
    }

    void Matrix::concat(const Pointer<Matrix> &matrix) {
        float a1 = a * matrix->a + b * matrix->c;
        b = a * matrix->b + b * matrix->d;
        a = a1;
        
        float c1 = c * matrix->a + d * matrix->c;
        d = c * matrix->b + d * matrix->d;
        c = c1;
        
        float tx1 = tx * matrix->a + ty * matrix->c + matrix->tx;
        ty = tx * matrix->b + ty * matrix->d + matrix->ty;
        tx = tx1;
    }

    void Matrix::copyColumnFrom(const uInt column, const Pointer<Vector3D> &vector) {
        if (column > 2) {
            // TODO: throw error
        } else if (column == 0) {
            a = vector->x;
            c = vector->y;
        } else if (column == 1) {
            b = vector->x;
            d = vector->y;
        } else {
            tx = vector->x;
            ty = vector->y;
        }
    }

    void Matrix::copyColumnTo(const uInt column, Pointer<Vector3D> &vector) const {
        if (column > 2) {
            // TODO: throw error
        } else if (column == 0) {
            vector->x = a;
            vector->y = c;
            vector->z = 0;
        } else if (column == 1) {
            vector->x = b;
            vector->y = d;
            vector->z = 0;
        } else {
            vector->x = tx;
            vector->y = ty;
            vector->z = 1;
        }
    }

    void Matrix::copyFrom(const Pointer<Matrix> &matrix) {
        a = matrix->a;
        b = matrix->b;
        c = matrix->c;
        d = matrix->d;
        tx = matrix->tx;
        ty = matrix->ty;
    }

    void Matrix::copyRowFrom(const uInt row, const Pointer<Vector3D> &vector) {
        if (row > 2) {
            // TODO: throw error
        } else if (row == 0) {
            a = vector->x;
            c = vector->y;
        } else if (row == 1) {
            b = vector->x;
            d = vector->y;
        } else {
            tx = vector->x;
            ty = vector->y;
        }
    }

    void Matrix::copyRowTo(const uInt row, Pointer<Vector3D> &vector) const {
        if (row > 2) {
            // TODO: throw error
        } else if (row == 0) {
            vector->x = a;
            vector->y = b;
            vector->z = tx;
        } else if (row == 1) {
            vector->x = c;
            vector->y = d;
            vector->z = ty;
        } else {
            vector->setTo (0, 0, 1);
        }
    }

    Pointer<Point> Matrix::deltaTransformPoint(const Pointer<Point> &point) const {
        return new Point(
            point->x * a + point->y * c,
            point->x * b + point->y * d
        );
    }

    bool Matrix::equals(const Pointer<Matrix> &matrix) const {
        return (
               tx == matrix->tx
            && ty == matrix->ty
            && a == matrix->a
            && b == matrix->b
            && c == matrix->c
            && d == matrix->d
        );
    }

    void Matrix::identity() {
        a = 1;
        b = 0;
        c = 0;
        d = 1;
        tx = 0;
        ty = 0;
    }

    void Matrix::invert() {
        float norm = a * d - b * c;

        if (norm == 0) {
            a = b = c = d = 0;
            tx = -tx;
            ty = -ty;
        } else {
            norm = 1.0f / norm;
            float a1 = d * norm;
            d = a * norm;
            a = a1;
            b *= -norm;
            c *= -norm;

            float tx1 = - a * tx - c * ty;
            ty = - b * tx - d * ty;
            tx = tx1;
        }
    }

    void Matrix::rotate(const float angle) {
        float cos = (float)utils::Math::cos(angle);
        float sin = (float)utils::Math::sin(angle);

        float a1 = a * cos - b * sin;
        b = a * sin + b * cos;
        a = a1;

        float c1 = c * cos - d * sin;
        d = c * sin + d * cos;
        c = c1;

        float tx1 = tx * cos - ty * sin;
        ty = tx * sin + ty * cos;
        tx = tx1;
    }

    void Matrix::scale(const float scaleX, const float scaleY) {
        a *= scaleX;
        b *= scaleY;
        c *= scaleX;
        d *= scaleY;
        tx *= scaleX;
        ty *= scaleY;
    }

    void Matrix::setTo(const float newA, const float newB, const float newC, const float newD, const float newTx, const float newTy) {
        a = newA;
        b = newB;
        c = newC;
        d = newD;
        tx = newTx;
        ty = newTy;
    }

    Pointer<Point> Matrix::transformPoint(const Pointer<Point> &point) const {
        return new Point(
            point->x * a + point->y * c + tx,
            point->x * b + point->y * d + ty
        );
    }

    void Matrix::translate(const float deltaX, const float deltaY) {
        tx += deltaX;
        ty += deltaY;
    }
}
