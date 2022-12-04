#include <flash/display3D/Stage3D.h>

namespace flash::display3D {
    Stage3D::Stage3D(sInt stageID) {
        _stageID = stageID;
    }

    Stage3D::~Stage3D() {
        // empty
    }

    Pointer<Context3D> Stage3D::requestContext3D() {
        if (context3D == nullptr) {
            context3D = new Context3D(_stageID);
        }

        return context3D;
    }
}
