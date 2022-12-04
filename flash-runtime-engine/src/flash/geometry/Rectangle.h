#ifndef FLASH_GEOMETRY_RECTANGLE_H
#define FLASH_GEOMETRY_RECTANGLE_H

#include <flash/geometry/Point.h>
#include <flash/core/Core.h>

namespace flash::geometry {
    class Rectangle : public Object {
        public:
            float width;
            float height;
            float x;
            float y;

        public:
            Rectangle(const float x = 0, const float y = 0, const float width = 0, const float height = 0);
           ~Rectangle() override;

        public:
            Pointer<Rectangle> clone() const;
            bool contains(const float pointX, const float pointY) const;
            bool containsPoint(const Pointer<Point> &point) const;
            bool containsRect(const Pointer<Rectangle> &rectangle) const;
            void copyFrom(const Pointer<Rectangle> &rectangle);
            bool equals(const Pointer<Rectangle> &rectangle) const;
            void inflate(const float deltaX, const float deltaY);
            void inflatePoint(const Pointer<Point> &point);
            Pointer<Rectangle> intersection(const Pointer<Rectangle> &rectangle) const;
            bool intersects(const Pointer<Rectangle> &rectangle) const;
            bool isEmpty() const;
            void offset(const float deltaX, const float deltaY);
            void offsetPoint(const Pointer<Point> &point);
            void setEmpty();
            void setTo(const float newX, const float newY, const float newWidth, const float newHeight);
            Pointer<Rectangle> merge(const Pointer<Rectangle> &rectangle);
            String toString() const override;

        public:
            float bottom() const;
            Pointer<Point> bottomRight() const;
            float left() const;
            float right() const;
            float top() const;
            Pointer<Point> topLeft() const;
    };
}

#endif
