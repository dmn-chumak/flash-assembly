#include <flash/geometry/Matrix3D.h>
#include <flash/utils/Math.h>

namespace flash::geometry {
    Matrix3D::Matrix3D(const Pointer<Vector<float>> &source) {
        rawData = new Vector<float>(16);
        identity();

        if (source != nullptr) {
            for (uInt i = 0; i < source->length(); i++) {
                rawData->source()[i] = source->obtainAt(i);
            }
        }
    }

    Matrix3D::~Matrix3D() {
        // empty
    }

    Pointer<Matrix3D> Matrix3D::interpolate(const Pointer<Matrix3D> &firstMatrix, const Pointer<Matrix3D> &secondMatrix, const float percent) {
        Pointer<Matrix3D> m = new Matrix3D ();

        for (uInt i = 0; i < 16; i++) {
            m->rawData->source()[i] = firstMatrix->rawData->obtainAt(i) + (secondMatrix->rawData->obtainAt(i) - firstMatrix->rawData->obtainAt(i)) * percent;
        }

        return m;
    }

    void Matrix3D::append(const Pointer<Matrix3D> &matrix) {
        float m111 = rawData->obtainAt(0), m121 = rawData->obtainAt(4), m131 = rawData->obtainAt(8), m141 = rawData->obtainAt(12);
        float m112 = rawData->obtainAt(1), m122 = rawData->obtainAt(5), m132 = rawData->obtainAt(9), m142 = rawData->obtainAt(13);
        float m113 = rawData->obtainAt(2), m123 = rawData->obtainAt(6), m133 = rawData->obtainAt(10), m143 = rawData->obtainAt(14);
        float m114 = rawData->obtainAt(3), m124 = rawData->obtainAt(7), m134 = rawData->obtainAt(11), m144 = rawData->obtainAt(15);

        float m211 = matrix->rawData->obtainAt(0), m221 = matrix->rawData->obtainAt(4), m231 = matrix->rawData->obtainAt(8), m241 = matrix->rawData->obtainAt(12);
        float m212 = matrix->rawData->obtainAt(1), m222 = matrix->rawData->obtainAt(5), m232 = matrix->rawData->obtainAt(9), m242 = matrix->rawData->obtainAt(13);
        float m213 = matrix->rawData->obtainAt(2), m223 = matrix->rawData->obtainAt(6), m233 = matrix->rawData->obtainAt(10), m243 = matrix->rawData->obtainAt(14);
        float m214 = matrix->rawData->obtainAt(3), m224 = matrix->rawData->obtainAt(7), m234 = matrix->rawData->obtainAt(11), m244 = matrix->rawData->obtainAt(15);

        rawData->source()[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
        rawData->source()[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
        rawData->source()[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
        rawData->source()[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;

        rawData->source()[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
        rawData->source()[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
        rawData->source()[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
        rawData->source()[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;

        rawData->source()[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
        rawData->source()[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
        rawData->source()[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
        rawData->source()[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;

        rawData->source()[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
        rawData->source()[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
        rawData->source()[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
        rawData->source()[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;
    }

    void Matrix3D::appendRotation(const float angle, const Pointer<Vector3D> &axis, const Pointer<Vector3D> pivot) {
        float tx = 0, ty = 0, tz = 0;

        if (pivot != nullptr) {
            tx = pivot->x;
            ty = pivot->y;
            tz = pivot->z;
        }

        float radian = (float)(angle * utils::Math::PI / 180.0);
        float cos = (float)utils::Math::cos(radian);
        float sin = (float)utils::Math::sin(radian);
        float x = axis->x;
        float y = axis->y;
        float z = axis->z;
        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;
        float ls = x2 + y2 + z2;

        if (ls != 0) {
            float l = (float)utils::Math::sqrt(ls);
            x /= l;
            y /= l;
            z /= l;
            x2 /= ls;
            y2 /= ls;
            z2 /= ls;
        }

        float ccos = 1 - cos;
        Pointer<Matrix3D> m = new Matrix3D();

        m->rawData->source()[0] = x2 + (y2 + z2) * cos;
        m->rawData->source()[1] = x * y * ccos + z * sin;
        m->rawData->source()[2] = x * z * ccos - y * sin;
        m->rawData->source()[4] = x * y * ccos - z * sin;
        m->rawData->source()[5] = y2 + (x2 + z2) * cos;
        m->rawData->source()[6] = y * z * ccos + x * sin;
        m->rawData->source()[8] = x * z * ccos + y * sin;
        m->rawData->source()[9] = y * z * ccos - x * sin;
        m->rawData->source()[10] = z2 + (x2 + y2) * cos;
        m->rawData->source()[12] = (tx * (y2 + z2) - x * (ty * y + tz * z)) * ccos + (ty * z - tz * y) * sin;
        m->rawData->source()[13] = (ty * (x2 + z2) - y * (tx * x + tz * z)) * ccos + (tz * x - tx * z) * sin;
        m->rawData->source()[14] = (tz * (x2 + y2) - z * (tx * x + ty * y)) * ccos + (tx * y - ty * x) * sin;

        append(m);
    }

    void Matrix3D::appendScale(const float scaleX, const float scaleY, const float scaleZ) {
        Pointer<Matrix3D> m = new Matrix3D();

        m->rawData->source()[0] = scaleX;
        m->rawData->source()[5] = scaleY;
        m->rawData->source()[10] = scaleZ;

        append(m);
    }

    void Matrix3D::appendTranslation(const float deltaX, const float deltaY, const float deltaZ) {
        rawData->source()[12] = rawData->obtainAt(12) + deltaX;
        rawData->source()[13] = rawData->obtainAt(13) + deltaY;
        rawData->source()[14] = rawData->obtainAt(14) + deltaZ;
    }

    Pointer<Matrix3D> Matrix3D::clone() const {
        Pointer<Matrix3D> m = new Matrix3D();

        for (uInt i = 0; i < 16; i++) {
            m->rawData->source()[i] = rawData->obtainAt(i);
        }

        return m;
    }

    void Matrix3D::copyColumnFrom(const uInt column, const Pointer<Vector3D> &vector) {
        switch (column) {
            case 0:
                rawData->source()[0] = vector->x;
                rawData->source()[1] = vector->y;
                rawData->source()[2] = vector->z;
                rawData->source()[3] = vector->w;
                break;

            case 1:
                rawData->source()[4] = vector->x;
                rawData->source()[5] = vector->y;
                rawData->source()[6] = vector->z;
                rawData->source()[7] = vector->w;
                break;

            case 2:
                rawData->source()[8] = vector->x;
                rawData->source()[9] = vector->y;
                rawData->source()[10] = vector->z;
                rawData->source()[11] = vector->w;
                break;

            case 3:
                rawData->source()[12] = vector->x;
                rawData->source()[13] = vector->y;
                rawData->source()[14] = vector->z;
                rawData->source()[15] = vector->w;
                break;

            default:
                // TODO: throw error
                break;
        }
    }

    void Matrix3D::copyColumnTo(const uInt column, Pointer<Vector3D> &vector) const {
        switch (column) {
            case 0:
                vector->x = rawData->obtainAt(0);
                vector->y = rawData->obtainAt(1);
                vector->z = rawData->obtainAt(2);
                vector->w = rawData->obtainAt(3);
                break;

            case 1:
                vector->x = rawData->obtainAt(4);
                vector->y = rawData->obtainAt(5);
                vector->z = rawData->obtainAt(6);
                vector->w = rawData->obtainAt(7);
                break;

            case 2:
                vector->x = rawData->obtainAt(8);
                vector->y = rawData->obtainAt(9);
                vector->z = rawData->obtainAt(10);
                vector->w = rawData->obtainAt(11);
                break;

            case 3:
                vector->x = rawData->obtainAt(12);
                vector->y = rawData->obtainAt(13);
                vector->z = rawData->obtainAt(14);
                vector->w = rawData->obtainAt(15);
                break;

            default:
                // TODO: throw error
                break;
        }
    }

    void Matrix3D::copyFrom(const Pointer<Matrix3D> &matrix) {
        for (uInt i = 0; i < 16; i++) {
            rawData->source()[i] = matrix->rawData->obtainAt(i);
        }
    }

    void Matrix3D::copyRawDataFrom(const Pointer<Vector<float>> &vector, uInt index, bool needTranspose) {
        if (needTranspose) {
            transpose();
        }

        uInt length = 16 - index;

        for (uInt i = 0; i < length; i++) {
            rawData->source()[i] = vector->obtainAt(i + index);
        }

        if (needTranspose) {
            transpose();
        }
    }

    void Matrix3D::copyRawDataTo(Pointer<Vector<float>> &vector, uInt index, bool needTranspose) {
        if (needTranspose) {
            transpose();
        }

        uInt length = 16 - index;

        for (uInt i = 0; i < length; i++) {
            vector->insertAt(i + index, rawData->obtainAt(i));
        }

        if (needTranspose) {
            transpose();
        }
    }

    void Matrix3D::copyRowFrom(const uInt row, const Pointer<Vector3D> &vector) {
        switch (row) {
            case 0:
                rawData->source()[0] = vector->x;
                rawData->source()[4] = vector->y;
                rawData->source()[8] = vector->z;
                rawData->source()[12] = vector->w;
                break;

            case 1:
                rawData->source()[1] = vector->x;
                rawData->source()[5] = vector->y;
                rawData->source()[9] = vector->z;
                rawData->source()[13] = vector->w;
                break;

            case 2:
                rawData->source()[2] = vector->x;
                rawData->source()[6] = vector->y;
                rawData->source()[10] = vector->z;
                rawData->source()[14] = vector->w;
                break;

            case 3:
                rawData->source()[3] = vector->x;
                rawData->source()[7] = vector->y;
                rawData->source()[11] = vector->z;
                rawData->source()[15] = vector->w;
                break;

            default:
                // TODO: throw error
                break;
        }
    }

    void Matrix3D::copyRowTo(const uInt row, Pointer<Vector3D> &vector) const {
        switch (row) {
            case 0:
                vector->x = rawData->obtainAt(0);
                vector->y = rawData->obtainAt(4);
                vector->z = rawData->obtainAt(8);
                vector->w = rawData->obtainAt(12);

            case 1:
                vector->x = rawData->obtainAt(1);
                vector->y = rawData->obtainAt(5);
                vector->z = rawData->obtainAt(9);
                vector->w = rawData->obtainAt(13);

            case 2:
                vector->x = rawData->obtainAt(2);
                vector->y = rawData->obtainAt(6);
                vector->z = rawData->obtainAt(10);
                vector->w = rawData->obtainAt(14);

            case 3:
                vector->x = rawData->obtainAt(3);
                vector->y = rawData->obtainAt(7);
                vector->z = rawData->obtainAt(11);
                vector->w = rawData->obtainAt(15);

            default:
                // TODO: throw error
                break;
        }
    }

    void Matrix3D::copyToMatrix(Pointer<Matrix3D> &matrix) const {
        for (uInt i = 0; i < 16; i++) {
            matrix->rawData->source()[i] = rawData->obtainAt(i);
        }
    }

    Pointer<Vector3D> Matrix3D::deltaTransformVector(const Pointer<Vector3D> &vector) {
        float x = vector->x, y = vector->y, z = vector->z;

        return new Vector3D(
            (x * rawData->obtainAt(0) + y * rawData->obtainAt(4) + z * rawData->obtainAt(8) + rawData->obtainAt(3)),
            (x * rawData->obtainAt(1) + y * rawData->obtainAt(5) + z * rawData->obtainAt(9) + rawData->obtainAt(7)),
            (x * rawData->obtainAt(2) + y * rawData->obtainAt(6) + z * rawData->obtainAt(10) + rawData->obtainAt(11)),
            0
        );
    }

    void Matrix3D::identity() {
        rawData->source()[0] = 1.0;
        rawData->source()[1] = 0;
        rawData->source()[2] = 0;
        rawData->source()[3] = 0;
        rawData->source()[4] = 0;
        rawData->source()[5] = 1.0;
        rawData->source()[6] = 0;
        rawData->source()[7] = 0;
        rawData->source()[8] = 0;
        rawData->source()[9] = 0;
        rawData->source()[10] = 1.0;
        rawData->source()[11] = 0;
        rawData->source()[12] = 0;
        rawData->source()[13] = 0;
        rawData->source()[14] = 0;
        rawData->source()[15] = 1.0;
    }

    void Matrix3D::interpolateTo(const Pointer<Matrix3D> &matrix, const float percent) {
        for (uInt i = 0; i < 16; i++) {
            rawData->source()[i] = rawData->obtainAt(i) + (matrix->rawData->obtainAt(i) - rawData->obtainAt(i)) * percent;
        }
    }

    bool Matrix3D::invert() {
        float d = determinant();
        bool invertable = utils::Math::abs (d) > 0.00000000001;

        if (invertable) {
            d = 1 / d;

            float m11 = rawData->obtainAt(0), m21 = rawData->obtainAt(4), m31 = rawData->obtainAt(8), m41 = rawData->obtainAt(12);
            float m12 = rawData->obtainAt(1), m22 = rawData->obtainAt(5), m32 = rawData->obtainAt(9), m42 = rawData->obtainAt(13);
            float m13 = rawData->obtainAt(2), m23 = rawData->obtainAt(6), m33 = rawData->obtainAt(10), m43 = rawData->obtainAt(14);
            float m14 = rawData->obtainAt(3), m24 = rawData->obtainAt(7), m34 = rawData->obtainAt(11), m44 = rawData->obtainAt(15);

            rawData->source()[0] = d * (m22 * (m33 * m44 - m43 * m34) - m32 * (m23 * m44 - m43 * m24) + m42 * (m23 * m34 - m33 * m24));
            rawData->source()[1] = -d * (m12 * (m33 * m44 - m43 * m34) - m32 * (m13 * m44 - m43 * m14) + m42 * (m13 * m34 - m33 * m14));
            rawData->source()[2] = d * (m12 * (m23 * m44 - m43 * m24) - m22 * (m13 * m44 - m43 * m14) + m42 * (m13 * m24 - m23 * m14));
            rawData->source()[3] = -d * (m12 * (m23 * m34 - m33 * m24) - m22 * (m13 * m34 - m33 * m14) + m32 * (m13 * m24 - m23 * m14));
            rawData->source()[4] = -d * (m21 * (m33 * m44 - m43 * m34) - m31 * (m23 * m44 - m43 * m24) + m41 * (m23 * m34 - m33 * m24));
            rawData->source()[5] = d * (m11 * (m33 * m44 - m43 * m34) - m31 * (m13 * m44 - m43 * m14) + m41 * (m13 * m34 - m33 * m14));
            rawData->source()[6] = -d * (m11 * (m23 * m44 - m43 * m24) - m21 * (m13 * m44 - m43 * m14) + m41 * (m13 * m24 - m23 * m14));
            rawData->source()[7] = d * (m11 * (m23 * m34 - m33 * m24) - m21 * (m13 * m34 - m33 * m14) + m31 * (m13 * m24 - m23 * m14));
            rawData->source()[8] = d * (m21 * (m32 * m44 - m42 * m34) - m31 * (m22 * m44 - m42 * m24) + m41 * (m22 * m34 - m32 * m24));
            rawData->source()[9] = -d * (m11 * (m32 * m44 - m42 * m34) - m31 * (m12 * m44 - m42 * m14) + m41 * (m12 * m34 - m32 * m14));
            rawData->source()[10] = d * (m11 * (m22 * m44 - m42 * m24) - m21 * (m12 * m44 - m42 * m14) + m41 * (m12 * m24 - m22 * m14));
            rawData->source()[11] = -d * (m11 * (m22 * m34 - m32 * m24) - m21 * (m12 * m34 - m32 * m14) + m31 * (m12 * m24 - m22 * m14));
            rawData->source()[12] = -d * (m21 * (m32 * m43 - m42 * m33) - m31 * (m22 * m43 - m42 * m23) + m41 * (m22 * m33 - m32 * m23));
            rawData->source()[13] = d * (m11 * (m32 * m43 - m42 * m33) - m31 * (m12 * m43 - m42 * m13) + m41 * (m12 * m33 - m32 * m13));
            rawData->source()[14] = -d * (m11 * (m22 * m43 - m42 * m23) - m21 * (m12 * m43 - m42 * m13) + m41 * (m12 * m23 - m22 * m13));
            rawData->source()[15] = d * (m11 * (m22 * m33 - m32 * m23) - m21 * (m12 * m33 - m32 * m13) + m31 * (m12 * m23 - m22 * m13));
        }

        return invertable;
    }

    void Matrix3D::pointAt(const Pointer<Vector3D> &vector, const Pointer<Vector3D> &at, const Pointer<Vector3D> &up) {
        Pointer<Vector3D> rat;
        Pointer<Vector3D> rup;

        if (at == nullptr) {
            rat = new Vector3D(0, 0, -1);
        } else {
            rat = at;
        }

        if (up == nullptr) {
            rup = new Vector3D(0, -1, 0);
        } else {
            rup = up;
        }

        Pointer<Vector3D> dir = rat->subtract(vector);
        Pointer<Vector3D> vup = rup->clone();
        Pointer<Vector3D> right;

        dir->normalize();
        vup->normalize();

        Pointer<Vector3D> dir2 = dir->clone ();
        dir2->scaleBy(vup->dotProduct(dir));

        vup = vup->subtract(dir2);

        if (vup->length() > 0) {
            vup->normalize ();
        } else {
            if (dir->x != 0) {
                vup = new Vector3D(-dir->y, dir->x, 0);
            } else {
                vup = new Vector3D(1, 0, 0);
            }
        }

        right = vup->crossProduct(dir);
        right->normalize();

        rawData->source()[0] = right->x;
        rawData->source()[4] = right->y;
        rawData->source()[8] = right->z;
        rawData->source()[12] = 0.0;
        rawData->source()[1] = vup->x;
        rawData->source()[5] = vup->y;
        rawData->source()[9] = vup->z;
        rawData->source()[13] = 0.0;
        rawData->source()[2] = dir->x;
        rawData->source()[6] = dir->y;
        rawData->source()[10] = dir->z;
        rawData->source()[14] = 0.0;
        rawData->source()[3] = vector->x;
        rawData->source()[7] = vector->y;
        rawData->source()[11] = vector->z;
        rawData->source()[15] = 1.0;
    }

    void Matrix3D::prepend(const Pointer<Matrix3D> &matrix) {
        float m111 = matrix->rawData->obtainAt(0), m121 = matrix->rawData->obtainAt(4), m131 = matrix->rawData->obtainAt(8), m141 = matrix->rawData->obtainAt(12);
        float m112 = matrix->rawData->obtainAt(1), m122 = matrix->rawData->obtainAt(5), m132 = matrix->rawData->obtainAt(9), m142 = matrix->rawData->obtainAt(13);
        float m113 = matrix->rawData->obtainAt(2), m123 = matrix->rawData->obtainAt(6), m133 = matrix->rawData->obtainAt(10), m143 = matrix->rawData->obtainAt(14);
        float m114 = matrix->rawData->obtainAt(3), m124 = matrix->rawData->obtainAt(7), m134 = matrix->rawData->obtainAt(11), m144 = matrix->rawData->obtainAt(15);
        float m211 = rawData->obtainAt(0), m221 = rawData->obtainAt(4), m231 = rawData->obtainAt(8), m241 = rawData->obtainAt(12);
        float m212 = rawData->obtainAt(1), m222 = rawData->obtainAt(5), m232 = rawData->obtainAt(9), m242 = rawData->obtainAt(13);
        float m213 = rawData->obtainAt(2), m223 = rawData->obtainAt(6), m233 = rawData->obtainAt(10), m243 = rawData->obtainAt(14);
        float m214 = rawData->obtainAt(3), m224 = rawData->obtainAt(7), m234 = rawData->obtainAt(11), m244 = rawData->obtainAt(15);

        rawData->source()[0] = m111 * m211 + m112 * m221 + m113 * m231 + m114 * m241;
        rawData->source()[1] = m111 * m212 + m112 * m222 + m113 * m232 + m114 * m242;
        rawData->source()[2] = m111 * m213 + m112 * m223 + m113 * m233 + m114 * m243;
        rawData->source()[3] = m111 * m214 + m112 * m224 + m113 * m234 + m114 * m244;

        rawData->source()[4] = m121 * m211 + m122 * m221 + m123 * m231 + m124 * m241;
        rawData->source()[5] = m121 * m212 + m122 * m222 + m123 * m232 + m124 * m242;
        rawData->source()[6] = m121 * m213 + m122 * m223 + m123 * m233 + m124 * m243;
        rawData->source()[7] = m121 * m214 + m122 * m224 + m123 * m234 + m124 * m244;

        rawData->source()[8] = m131 * m211 + m132 * m221 + m133 * m231 + m134 * m241;
        rawData->source()[9] = m131 * m212 + m132 * m222 + m133 * m232 + m134 * m242;
        rawData->source()[10] = m131 * m213 + m132 * m223 + m133 * m233 + m134 * m243;
        rawData->source()[11] = m131 * m214 + m132 * m224 + m133 * m234 + m134 * m244;

        rawData->source()[12] = m141 * m211 + m142 * m221 + m143 * m231 + m144 * m241;
        rawData->source()[13] = m141 * m212 + m142 * m222 + m143 * m232 + m144 * m242;
        rawData->source()[14] = m141 * m213 + m142 * m223 + m143 * m233 + m144 * m243;
        rawData->source()[15] = m141 * m214 + m142 * m224 + m143 * m234 + m144 * m244;
    }

    void Matrix3D::prependRotation(const float angle, const Pointer<Vector3D> &axis, const Pointer<Vector3D> pivot) {
        float tx = 0, ty = 0, tz = 0;

        if (pivot != nullptr) {
            tx = pivot->x;
            ty = pivot->y;
            tz = pivot->z;
        }

        float radian = (float)(angle * utils::Math::PI / 180);
        float cos = (float)utils::Math::cos(radian);
        float sin = (float)utils::Math::sin(radian);
        float x = axis->x;
        float y = axis->y;
        float z = axis->z;
        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;
        float ls = x2 + y2 + z2;
        if (ls != 0) {
            float l = (float)utils::Math::sqrt(ls);
            x /= l;
            y /= l;
            z /= l;
            x2 /= ls;
            y2 /= ls;
            z2 /= ls;
        }
        float ccos = 1 - cos;
        Pointer<Matrix3D> m = new Matrix3D();

        m->rawData->source()[0] = x2 + (y2 + z2) * cos;
        m->rawData->source()[1] = x * y * ccos + z * sin;
        m->rawData->source()[2] = x * z * ccos - y * sin;
        m->rawData->source()[4] = x * y * ccos - z * sin;
        m->rawData->source()[5] = y2 + (x2 + z2) * cos;
        m->rawData->source()[6] = y * z * ccos + x * sin;
        m->rawData->source()[8] = x * z * ccos + y * sin;
        m->rawData->source()[9] = y * z * ccos - x * sin;
        m->rawData->source()[10] = z2 + (x2 + y2) * cos;
        m->rawData->source()[12] = (tx * (y2 + z2) - x * (ty * y + tz * z)) * ccos + (ty * z - tz * y) * sin;
        m->rawData->source()[13] = (ty * (x2 + z2) - y * (tx * x + tz * z)) * ccos + (tz * x - tx * z) * sin;
        m->rawData->source()[14] = (tz * (x2 + y2) - z * (tx * x + ty * y)) * ccos + (tx * y - ty * x) * sin;

        prepend(m);
    }

    void Matrix3D::prependScale(const float scaleX, const float scaleY, const float scaleZ) {
        Pointer<Matrix3D> m = new Matrix3D();

        m->rawData->source()[0] = scaleX;
        m->rawData->source()[5] = scaleY;
        m->rawData->source()[10] = scaleZ;

        prepend(m);
    }

    void Matrix3D::prependTranslation(const float deltaX, const float deltaY, const float deltaZ) {
        Pointer<Matrix3D> m = new Matrix3D ();
        m->setPosition(new Vector3D(deltaX, deltaY, deltaZ));
        prepend(m);
    }

    Pointer<Vector3D> Matrix3D::transformVector(const Pointer<Vector3D> &vector) {
        float x = vector->x;
        float y = vector->y;
        float z = vector->z;

        return new Vector3D (
            (x * rawData->obtainAt(0) + y * rawData->obtainAt(4) + z * rawData->obtainAt(8) + rawData->obtainAt(12)),
            (x * rawData->obtainAt(1) + y * rawData->obtainAt(5) + z * rawData->obtainAt(9) + rawData->obtainAt(13)),
            (x * rawData->obtainAt(2) + y * rawData->obtainAt(6) + z * rawData->obtainAt(10) + rawData->obtainAt(14)),
            (x * rawData->obtainAt(3) + y * rawData->obtainAt(7) + z * rawData->obtainAt(11) + rawData->obtainAt(15))
        );
    }

    void Matrix3D::transformVectors() {

    }

    void Matrix3D::transpose() {
        Pointer<Vector<float>> oRawData = new Vector<float>(16);

        for (uInt i = 0; i < 16; i++) {
            oRawData->source()[i] = rawData->obtainAt(i);
        }

        rawData->source()[1] = oRawData->obtainAt(4);
        rawData->source()[2] = oRawData->obtainAt(8);
        rawData->source()[3] = oRawData->obtainAt(12);
        rawData->source()[4] = oRawData->obtainAt(1);
        rawData->source()[6] = oRawData->obtainAt(9);
        rawData->source()[7] = oRawData->obtainAt(13);
        rawData->source()[8] = oRawData->obtainAt(2);
        rawData->source()[9] = oRawData->obtainAt(6);
        rawData->source()[11] = oRawData->obtainAt(14);
        rawData->source()[12] = oRawData->obtainAt(3);
        rawData->source()[13] = oRawData->obtainAt(7);
        rawData->source()[14] = oRawData->obtainAt(11);
    }

    bool Matrix3D::recompose(Pointer<Array<Vector3D>> components, String &orientationStyle) {
        return false;
    }

    Pointer<Array<Vector3D>> Matrix3D::decompose(String &orientationStyle) {
        return nullptr;
    }

    float Matrix3D::determinant() const {
        return (
            1 * ((rawData->obtainAt(0) * rawData->obtainAt(5) - rawData->obtainAt(4) * rawData->obtainAt(1)) * (rawData->obtainAt(10) * rawData->obtainAt(15) - rawData->obtainAt(14) * rawData->obtainAt(11))
            - (rawData->obtainAt(0) * rawData->obtainAt(9) - rawData->obtainAt(8) * rawData->obtainAt(1)) * (rawData->obtainAt(6) * rawData->obtainAt(15) - rawData->obtainAt(14) * rawData->obtainAt(7))
            + (rawData->obtainAt(0) * rawData->obtainAt(13) - rawData->obtainAt(12) * rawData->obtainAt(1)) * (rawData->obtainAt(6) * rawData->obtainAt(11) - rawData->obtainAt(10) * rawData->obtainAt(7))
            + (rawData->obtainAt(4) * rawData->obtainAt(9) - rawData->obtainAt(8) * rawData->obtainAt(5)) * (rawData->obtainAt(2) * rawData->obtainAt(15) - rawData->obtainAt(14) * rawData->obtainAt(3))
            - (rawData->obtainAt(4) * rawData->obtainAt(13) - rawData->obtainAt(12) * rawData->obtainAt(5)) * (rawData->obtainAt(2) * rawData->obtainAt(11) - rawData->obtainAt(10) * rawData->obtainAt(3))
            + (rawData->obtainAt(8) * rawData->obtainAt(13) - rawData->obtainAt(12) * rawData->obtainAt(9)) * (rawData->obtainAt(2) * rawData->obtainAt(7) - rawData->obtainAt(6) * rawData->obtainAt(3)))
        );
    }

    void Matrix3D::setPosition(Pointer<Vector3D> vector) {
        rawData->source()[12] = vector->x;
        rawData->source()[13] = vector->y;
        rawData->source()[14] = vector->z;
    }

    Pointer<Vector3D> Matrix3D::getPosition() {
        return new Vector3D(rawData->obtainAt(12), rawData->obtainAt(13), rawData->obtainAt(14));
    }
}
