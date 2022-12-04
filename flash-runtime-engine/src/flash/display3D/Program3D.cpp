#include <flash/display3D/Program3D.h>
#include <flash/runtime/Canvas.h>
#include <flash/display3D/shaders/AbstractShader.h>

using flash::runtime::Canvas::ProgramType;

namespace flash::display3D {
    Program3D::Program3D() {
        // empty
    }

    Program3D::~Program3D() {
        dispose();
    }

    void Program3D::upload(const String &vertexProgram, const String &fragmentProgram) {
        AbstractShader vertexShader;
        vertexShader.compile(vertexProgram, ProgramType::VERTEX_SHADER);

        AbstractShader fragmentShader;
        fragmentShader.compile(fragmentProgram, ProgramType::FRAGMENT_SHADER);

        _programID = runtime::Canvas::createProgram();
        runtime::Canvas::attachShader(_programID, vertexShader.shaderID());
        runtime::Canvas::attachShader(_programID, fragmentShader.shaderID());
        runtime::Canvas::linkProgram(_programID);
        runtime::Canvas::validateProgram(_programID);

        if (!runtime::Canvas::checkProgramStatus(_programID)) {
            // TODO: handle program status
        }

        for (uInt i = 0; i < 4; i++) {
            String reg = String("reg") + i;
            String uni = String("uni") + i;
            String tex = String("tex") + i;

            _registersIDs[i] = runtime::Canvas::getAttribLocation(
                _programID, reg.source(), reg.length()
            );

            _constantsIDs[i] = runtime::Canvas::getUniformLocation(
                _programID, uni.source(), uni.length()
            );

            _samplersIDs[i] = runtime::Canvas::getUniformLocation(
                _programID, tex.source(), tex.length()
            );
        }
    }

    void Program3D::dispose() {
        runtime::Canvas::deleteProgram(_programID);
    }

    sInt Program3D::registerID(const uInt index) const {
        return _registersIDs[index];
    }

    sInt Program3D::constantID(const uInt index) const {
        return _constantsIDs[index];
    }

    sInt Program3D::samplerID(const uInt index) const {
        return _samplersIDs[index];
    }

    sInt Program3D::programID() const {
        return _programID;
    }
}