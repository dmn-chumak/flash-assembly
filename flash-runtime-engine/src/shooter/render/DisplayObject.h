#ifndef SHOOTER_RENDER_DISPLAY_OBJECT_H
#define SHOOTER_RENDER_DISPLAY_OBJECT_H

#include <flash/core/Core.h>
#include <flash/geometry/Matrix.h>

using flash::geometry::Matrix;

namespace shooter::render {
    class IRender {

    };

    class DisplayObject : public Object {
        private:
        protected:
            bool _isMatrixValid;
            Pointer<DisplayObject> _parent;
            Pointer<Matrix> _matrix;
            double _rotation;
            double _scaleX;
            double _scaleY;
            double _pivotX;
            double _pivotY;
            double _x;
            double _y;
        public:
            DisplayObject();
            DisplayObject *DisplayObjectConstruct();
            virtual void render(IRender *renderer);
            virtual void update(double delta);
            double rotationGetter();
            void rotationSetter(double value);
            Pointer<DisplayObject> parentGetter();
            void parentSetter(Pointer<DisplayObject> value);
            double scaleXGetter();
            void scaleXSetter(double value);
            double scaleYGetter();
            void scaleYSetter(double value);
            double pivotXGetter();
            void pivotXSetter(double value);
            double pivotYGetter();
            void pivotYSetter(double value);
            double xGetter();
            void xSetter(double value);
            double yGetter();
            void ySetter(double value);
            Pointer<Matrix> matrixGetter();
            virtual ~DisplayObject() override;
    };
}

#endif

