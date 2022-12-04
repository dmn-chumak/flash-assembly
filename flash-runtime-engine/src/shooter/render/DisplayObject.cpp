#include <shooter/render/DisplayObject.h>
#include <flash/utils/Math.h>

using flash::utils::Math;

namespace shooter::render {
    DisplayObject::DisplayObject() {
        _isMatrixValid = false;
        _parent = nullptr;
        _matrix = nullptr;
        _rotation = 0;
        _scaleX = 0;
        _scaleY = 0;
        _pivotX = 0;
        _pivotY = 0;
        _x = 0;
        _y = 0;
    }

    DisplayObject *DisplayObject::DisplayObjectConstruct() {
        _isMatrixValid = true;
        _matrix = new Matrix();
        _rotation = Double(0);
        _scaleX = Double(1);
        _scaleY = Double(1);
        _pivotX = Double(0);
        _pivotY = Double(0);
        _x = Double(0);
        _y = Double(0);
        return this;
    }

    void DisplayObject::render(IRender *renderer) {
    }

    void DisplayObject::update(double delta) {
    }

    double DisplayObject::rotationGetter() {
        return _rotation;
    }

    void DisplayObject::rotationSetter(double value) {
        _isMatrixValid = false;
        _rotation = value;
    }

    Pointer<DisplayObject> DisplayObject::parentGetter() {
        return _parent;
    }

    void DisplayObject::parentSetter(Pointer<DisplayObject> value) {
        _parent = value;
    }

    double DisplayObject::scaleXGetter() {
        return _scaleX;
    }

    void DisplayObject::scaleXSetter(double value) {
        _isMatrixValid = false;
        _scaleX = value;
    }

    double DisplayObject::scaleYGetter() {
        return _scaleY;
    }

    void DisplayObject::scaleYSetter(double value) {
        _isMatrixValid = false;
        _scaleY = value;
    }

    double DisplayObject::pivotXGetter() {
        return _pivotX;
    }

    void DisplayObject::pivotXSetter(double value) {
        _isMatrixValid = false;
        _pivotX = value;
    }

    double DisplayObject::pivotYGetter() {
        return _pivotY;
    }

    void DisplayObject::pivotYSetter(double value) {
        _isMatrixValid = false;
        _pivotY = value;
    }

    double DisplayObject::xGetter() {
        return _x;
    }

    void DisplayObject::xSetter(double value) {
        _isMatrixValid = false;
        _x = value;
    }

    double DisplayObject::yGetter() {
        return _y;
    }

    void DisplayObject::ySetter(double value) {
        _isMatrixValid = false;
        _y = value;
    }

    Pointer<Matrix> DisplayObject::matrixGetter() {
        double cos = 0;
        double sin = 0;
        double a = 0;
        double b = 0;
        double c = 0;
        double d = 0;
        double x = 0;
        double y = 0;
        if (_isMatrixValid == true) {
            return _matrix;
        }
        _isMatrixValid = true;
        if (_rotation == Double(0)) {
            _matrix->setTo(_scaleX, Double(0), Double(0), _scaleY, _x - _pivotX * _scaleX, _y - _pivotY * _scaleY);
        } else {
            cos = Math::cos(_rotation);
            sin = Math::sin(_rotation);
            a = _scaleX * cos;
            b = _scaleX * sin;
            c = _scaleY * -sin;
            d = _scaleY * cos;
            x = _x - _pivotX * a - _pivotY * c;
            y = _y - _pivotX * b - _pivotY * d;
            _matrix->setTo(a, b, c, d, x, y);
        }
        return _matrix;
    }

    DisplayObject::~DisplayObject() {
    }
}

