#ifndef FLASH_GEOMETRY_POINT_H
#define FLASH_GEOMETRY_POINT_H

#include <flash/core/Core.h>

namespace flash::geometry {
    class Point final : public Object {
        public:
            float x;
            float y;

        public:
            Point(const float x = 0, const float y = 0);
           ~Point() override;

        public:
            static float distance(const Pointer<Point> &firstPoint, const Pointer<Point> &secondPoint);
            static Pointer<Point> interpolate(const Pointer<Point> &firstPoint, const Pointer<Point> &secondPoint, const float percent);
            static Pointer<Point> polar(const float length, const float angle);

        public:
            Pointer<Point> add(const Pointer<Point> &point) const;
            Pointer<Point> clone() const;
            void copyFrom(const Pointer<Point> &point);
            bool equals(const Pointer<Point> &point) const;
            void normalize(const float thickness);
            void offset(const float deltaX, const float deltaY);
            void setTo(const float newX, const float newY);
            Pointer<Point> subtract(const Pointer<Point> &point) const;
            String toString() const override;

        public:
            float length() const;
    };
}

#endif
