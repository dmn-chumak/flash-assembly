#include <flash/geometry/Rectangle.h>
#include <flash/utils/Math.h>

namespace flash::geometry {
    Rectangle::Rectangle(const float x, const float y, const float width, const float height)
    : width(width), height(height), x(x), y(y) {
        // empty
    }

    Rectangle::~Rectangle() {
        // empty
    }

    Pointer<Rectangle> Rectangle::clone() const {
        return new Rectangle(x, y, width, height);
    }

    bool Rectangle::contains(const float pointX, const float pointY) const {
        return (
               pointX <= x + width
            && pointY <= y + height
            && pointX >= x
            && pointY >= y
        );
    }

    bool Rectangle::containsPoint(const Pointer<Point> &point) const {
        return contains(point->x, point->y);
    }

    bool Rectangle::containsRect(const Pointer<Rectangle> &rectangle) const {
        return (
               rectangle->x + width < x + width
            && rectangle->y + height < y + height
            && rectangle->x > x
            && rectangle->y > y
        );
    }

    void Rectangle::copyFrom(const Pointer<Rectangle> &rectangle) {
        width = rectangle->width;
        height = rectangle->height;
        x = rectangle->x;
        y = rectangle->y;
    }

    bool Rectangle::equals(const Pointer<Rectangle> &rectangle) const {
        return (
               utils::Math::equal(width, rectangle->width)
            && utils::Math::equal(height, rectangle->height)
            && utils::Math::equal(x, rectangle->x)
            && utils::Math::equal(y, rectangle->y)
        );
    }

    void Rectangle::inflate(const float deltaX, const float deltaY) {
        width += 2.0 * deltaX;
        height += 2.0 * deltaY;
        x -= deltaX;
        y -= deltaY;
    }

    void Rectangle::inflatePoint(const Pointer<Point> &point) {
        inflate(point->x, point->y);
    }

    Pointer<Rectangle> Rectangle::intersection(const Pointer<Rectangle> &rectangle) const {
        float x0 = x < rectangle->x ? rectangle->x : x;
        float x1 = right() > rectangle->right() ? rectangle->right() : right();

        if (x1 <= x0) {
            return new Rectangle();
        }

        float y0 = y < rectangle->y ? rectangle->y : y;
        float y1 = bottom() > rectangle->bottom() ? rectangle->bottom() : bottom();

        if (y1 <= y0) {
            return new Rectangle();
        }

        return new Rectangle(x0, y0, x1 - x0, y1 - y0);
    }

    bool Rectangle::intersects(const Pointer<Rectangle> &rectangle) const {
        float x0 = x < rectangle->x ? rectangle->x : x;
        float x1 = right() > rectangle->right() ? rectangle->right() : right();

        if (x1 <= x0) {
            return false;
        }

        float y0 = y < rectangle->y ? rectangle->y : y;
        float y1 = bottom() > rectangle->bottom() ? rectangle->bottom() : bottom();

        return y1 > y0;
    }

    bool Rectangle::isEmpty() const {
        return (width <= 0 || height <= 0);
    }

    void Rectangle::offset(const float deltaX, const float deltaY) {
        x += deltaX;
        y += deltaY;
    }

    void Rectangle::offsetPoint(const Pointer<Point> &point) {
        x += point->x;
        y += point->y;
    }

    void Rectangle::setEmpty() {
        width = 0;
        height = 0;
        x = 0;
        y = 0;
    }

    void Rectangle::setTo(const float newX, const float newY, const float newWidth, const float newHeight) {
        width = newWidth;
        height = newHeight;
        x = newX;
        y = newY;
    }

    Pointer<Rectangle> Rectangle::merge(const Pointer<Rectangle> &rectangle) {
        if (width == 0 || height == 0) {
            return rectangle->clone();
        } else if (rectangle->width == 0 || rectangle->height == 0) {
            return clone();
        }

        float x0 = x > rectangle->x ? rectangle->x : x;
        float x1 = right() < rectangle->right() ? rectangle->right() : right();
        float y0 = y > rectangle->y ? rectangle->y : y;
        float y1 = bottom() < rectangle->bottom() ? rectangle->bottom() : bottom();

        return new Rectangle(x0, y0, x1 - x0, y1 - y0);
    }

    String Rectangle::toString() const {
        return String() + "(x=" + x + ", y=" + y + ", width=" + width + ", height=" + height + ")";
    }

    float Rectangle::bottom() const {
        return y + height;
    }

    Pointer<Point> Rectangle::bottomRight() const {
        return new Point(x + width, y + height);
    }

    float Rectangle::left() const {
        return x;
    }

    float Rectangle::right() const {
        return x + width;
    }

    float Rectangle::top() const {
        return y;
    }

    Pointer<Point> Rectangle::topLeft() const {
        return new Point(x, y);
    }
}
