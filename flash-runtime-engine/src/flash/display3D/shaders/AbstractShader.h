#ifndef FLASH_DISPLAY_3D_SHADERS_ABSTRACTSHADER_H
#define FLASH_DISPLAY_3D_SHADERS_ABSTRACTSHADER_H

#include <flash/core/Core.h>
#include <flash/runtime/Canvas.h>

namespace flash::display3D {
    class AbstractShader {
        private:
            sInt _id;

        public:
            AbstractShader() = default;
            AbstractShader(const AbstractShader&) = delete;
            AbstractShader(AbstractShader&&) = default;
            AbstractShader& operator=(const AbstractShader&) = delete;
            AbstractShader& operator=(AbstractShader&&) = default;
            ~AbstractShader();

            void compile(const String& shaderProgram, runtime::Canvas::ProgramType type);

            sInt shaderID() const;
            void dispose();
    };
}

#endif
