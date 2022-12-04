#include <flash/display3D/shaders/AbstractShader.h>

namespace flash::display3D {
    AbstractShader::~AbstractShader() {
        dispose();
    }

    void AbstractShader::compile(const String& shaderProgram, runtime::Canvas::ProgramType type) {
        dispose();

        _id = runtime::Canvas::createShader(type);
        runtime::Canvas::shaderSource(_id, shaderProgram.source(), shaderProgram.length());
        runtime::Canvas::compileShader(_id);

        if (!runtime::Canvas::checkShaderStatus(_id)) {
            // TODO: handle shader status
        }
    }

    void AbstractShader::dispose() {
        runtime::Canvas::deleteShader(_id);
    }

    sInt AbstractShader::shaderID() const {
        return _id;
    }
}

