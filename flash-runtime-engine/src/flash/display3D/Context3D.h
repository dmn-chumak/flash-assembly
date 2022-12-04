#ifndef FLASH_DISPLAY_3D_CONTEXT_3D_H
#define FLASH_DISPLAY_3D_CONTEXT_3D_H

#include <flash/events/EventDispatcher.h>
#include <flash/display3D/Context3DClearMask.h>
#include <flash/display3D/Context3DBufferUsage.h>
#include <flash/display3D/Context3DMipFilter.h>
#include <flash/display3D/Context3DTextureFilter.h>
#include <flash/display3D/Context3DVertexBufferFormat.h>
#include <flash/display3D/Context3DTriangleFace.h>
#include <flash/display3D/Context3DCompareMode.h>
#include <flash/display3D/Context3DStencilAction.h>
#include <flash/display3D/Context3DWrapMode.h>
#include <flash/display3D/IndexBuffer3D.h>
#include <flash/display3D/Program3D.h>
#include <flash/display3D/VertexBuffer3D.h>
#include <flash/display3D/Texture3D.h>
#include <flash/runtime/Canvas.h>
#include <flash/core/Core.h>
#include <flash/utils/ByteArray.h>
#include <flash/geometry/Matrix3D.h>

namespace flash::display3D {
    class Context3D final : public events::EventDispatcher {
        private:
            Pointer<Program3D> _activeProgram;
            Pointer<Texture3D> _renderTarget;
            sInt _contextID;
            uInt _width;
            uInt _height;
            bool _enableDepthAndStencil;
            sInt _antiAlias;

        public:
            Context3D(sInt contextID);
           ~Context3D() override;

        public:
            void clear(float red = 0.0f, float green = 0.0f, float blue = 0.0f, float alpha = 1.0f, float depth = 1.0f, uInt stencil = 0, uInt mask = Context3DClearMask::ALL);
            void configureBackBuffer(uInt width, uInt height, sInt antiAlias, bool enableDepthAndStencil = false);
            Pointer<IndexBuffer3D> createIndexBuffer(uInt numIndices, const String &bufferUsage = Context3DBufferUsage::STATIC_DRAW);
            Pointer<Program3D> createProgram();
            Pointer<Texture3D> createTexture(uInt width, uInt height);
            Pointer<VertexBuffer3D> createVertexBuffer(uInt numVertices, uInt data32PerVertex, const String &bufferUsage = Context3DBufferUsage::STATIC_DRAW);
            void dispose(bool recreate = true);
            void drawTriangles(const Pointer<IndexBuffer3D> &indexBuffer, sInt firstIndex = 0, sInt numTriangles = -1);
            void present();
            void setBlendFactors(const String &sourceFactor, const String &destinationFactor);
            void setColorMask(bool red, bool green, bool blue, bool alpha);
            void setCulling(const String &triangleFaceToCull);
            void setDepthTest(bool depthMask, const String &passCompareMode);
            void setProgram(const Pointer<Program3D> &program);
            void setProgramConstantsFromBytes(const String &programType, sInt firstRegister, sInt numRegisters, const sByte *data);
            void setProgramConstantsFromByteArray(const String &programType, sInt firstRegister, sInt numRegisters, const Pointer<utils::ByteArray> &data, uInt byteArrayOffset);
            void setProgramConstantsFromMatrix(const String &programType, sInt firstRegister, const Pointer<geometry::Matrix3D> &data, bool transposedMatrix = false);
            void setProgramConstantsFromVector(const String &programType, sInt firstRegister, const Pointer<Vector<float>> &data, sInt numRegisters = -1);
            void setRenderToBackBuffer();
            void setRenderToTexture(const Pointer<Texture3D> &texture, bool enableDepthAndStencil = false, sInt antiAlias = 0, sInt surfaceSelector = 0, sInt colorOutputIndex = 0);
            void setSamplerStateAt(uInt sampler, const String &wrapMode, const String &texFilter, const String &mipFilter);
            void setScissorRectangle(const Pointer<geometry::Rectangle> &rectangle);
            void setStencilActions(const String &triangleFace = Context3DTriangleFace::FRONT_AND_BACK, const String &compareMode = Context3DCompareMode::ALWAYS, const String &actionOnBothPass = Context3DStencilAction::KEEP, const String &actionOnDepthFail = Context3DStencilAction::KEEP, const String &actionOnDepthPassStencilFail = Context3DStencilAction::KEEP);
            void setStencilReferenceValue(const uInt reference, const uInt readMask = 0xFF, const uInt writeMask = 0xFF);
            void setTextureAt(uInt sampler, const Pointer<Texture3D> &texture);
            void setVertexBufferAt(uInt index, const Pointer<VertexBuffer3D> &vertexBuffer, uInt bufferOffset, const String &format = Context3DVertexBufferFormat::FLOAT_4);
    };
}

#endif
