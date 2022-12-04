#include <flash/geometry/Point.h>
#include <flash/utils/Math.h>

namespace flash::geometry {
    Point::Point(const float x, const float y)
    : x(x), y(y) {
        // empty
    }

    Point::~Point() {
        // empty
    }

    float Point::distance(const Pointer<Point> &firstPoint, const Pointer<Point> &secondPoint) {
        float dx = firstPoint->x - firstPoint->x;
        float dy = firstPoint->y - firstPoint->y;
        return (float)utils::Math::sqrt(dx * dx + dy * dy);
    }

    Pointer<Point> Point::interpolate(const Pointer<Point> &firstPoint, const Pointer<Point> &secondPoint, const float percent) {
        return new Point(
            secondPoint->x + percent * (firstPoint->x - secondPoint->x),
            secondPoint->y + percent * (firstPoint->y - secondPoint->y)
        );
    }

    Pointer<Point> Point::polar(const float length, const float angle) {
        return new Point(
            length * (float)utils::Math::cos(angle),
            length * (float)utils::Math::sin(angle)
        );
    }

    Pointer<Point> Point::add(const Pointer<Point> &point) const {
        return new Point(
            x + point->x,
            y + point->y
        );
    }

    Pointer<Point> Point::clone() const {
        return new Point(x, y);
    }

    void Point::copyFrom(const Pointer<Point> &point) {
        x = point->x;
        y = point->y;
    }

    bool Point::equals(const Pointer<Point> &point) const {
        return (
               utils::Math::equal(x, point->x)
            && utils::Math::equal(y, point->y)
        );
    }

    void Point::normalize(const float thickness) {
        if (x != 0 || y != 0) {
            float norm = thickness / (float)utils::Math::sqrt (x * x + y * y);
            x *= norm;
            y *= norm;
        }
    }

    void Point::offset(const float deltaX, const float deltaY) {
        x += deltaX;
        y += deltaY;
    }

    void Point::setTo(const float newX, const float newY) {
        x = newX;
        y = newY;
    }

    Pointer<Point> Point::subtract(const Pointer<Point> &point) const {
        return new Point(
            x - point->x,
            y - point->y
        );
    }

    String Point::toString() const {
        return String() + "(x=" + x + ", y=" + y + ")";
    }

    float Point::length() const {
        return (float)utils::Math::sqrt(x * x + y * y);
    }
}
