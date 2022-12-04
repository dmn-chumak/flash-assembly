#include <flash/display3D/Context3D.h>
#include <flash/display3D/Context3DBlendFactor.h>
#include <flash/runtime/Number.h>

using namespace flash::runtime;
using Canvas::ContextCapability;
using Canvas::BufferTarget;
using Canvas::RenderMode;
using Canvas::DataType;

namespace flash::display3D {
    Context3D::Context3D(sInt contextID) {
        _activeProgram = nullptr;
        _contextID = contextID;
    }

    Context3D::~Context3D() {
        // empty
    }

    void Context3D::clear(float red, float green, float blue, float alpha, float depth, uInt stencil, uInt mask) {
        Canvas::clearColor(red, green, blue, alpha);
        Canvas::clearDepth(depth);
        Canvas::clearStencil(stencil);
        Canvas::clear(Context3DClearMask::translate(mask));
    }

    void Context3D::configureBackBuffer(uInt width, uInt height, sInt antiAlias, bool enableDepthAndStencil) {
        Canvas::viewport(0, 0, width, height);

        _height = height;
        _width = width;
        _enableDepthAndStencil = enableDepthAndStencil;
        _antiAlias = antiAlias;

        if (enableDepthAndStencil) {
            Canvas::enable(ContextCapability::STENCIL_TEST);
            Canvas::enable(ContextCapability::DEPTH_TEST);
        } else {
            Canvas::disable(ContextCapability::STENCIL_TEST);
            Canvas::disable(ContextCapability::DEPTH_TEST);
        }
    }

    Pointer<IndexBuffer3D> Context3D::createIndexBuffer(uInt numIndices, const String &bufferUsage) {
        return new IndexBuffer3D(numIndices, bufferUsage);
    }

    Pointer<Program3D> Context3D::createProgram() {
        return new Program3D();
    }

    Pointer<Texture3D> Context3D::createTexture(uInt width, uInt height) {
        return new Texture3D(width, height);
    }

    Pointer<VertexBuffer3D> Context3D::createVertexBuffer(uInt numVertices, uInt data32PerVertex, const String &bufferUsage) {
        return new VertexBuffer3D(numVertices, data32PerVertex, bufferUsage);
    }

    void Context3D::dispose(bool recreate) {
        // empty
    }

    void Context3D::drawTriangles(const Pointer<IndexBuffer3D> &indexBuffer, sInt firstIndex, sInt numTriangles) {
        Canvas::bindBuffer(BufferTarget::ELEMENT_ARRAY_BUFFER, indexBuffer->bufferID());
        Canvas::drawElements(RenderMode::TRIANGLES, ((numTriangles > 0) ? numTriangles * 3 : indexBuffer->numIndices()), DataType::UNSIGNED_SHORT, firstIndex);
    }

    void Context3D::present() {
        // empty
    }

    void Context3D::setBlendFactors(const String &sourceFactor, const String &destinationFactor) {
        Canvas::enable(ContextCapability::BLEND);
        Canvas::blendFunc(Context3DBlendFactor::translate(sourceFactor), Context3DBlendFactor::translate(destinationFactor));
    }

    void Context3D::setColorMask(bool red, bool green, bool blue, bool alpha) {
        Canvas::colorMask(red, green, blue, alpha);
    }

    void Context3D::setCulling(const String &triangleFaceToCull) {
        if (triangleFaceToCull == Context3DTriangleFace::NONE) {
            Canvas::disable(ContextCapability::CULL_FACE);
        } else {
            Canvas::enable(ContextCapability::CULL_FACE);
            Canvas::cullFace(Context3DTriangleFace::translate(triangleFaceToCull));
        }
    }

    void Context3D::setDepthTest(bool depthMask, const String &passCompareMode) {
        Canvas::depthMask(depthMask);
        Canvas::depthFunc(Context3DCompareMode::translate(passCompareMode));
    }

    void Context3D::setProgram(const Pointer<Program3D> &program) {
        Canvas::useProgram(program->programID());
        _activeProgram = program;
    }

    void Context3D::setProgramConstantsFromBytes(const String &programType, sInt firstRegister, sInt numRegisters, const sByte *data) {
        for (uInt i = 0; i < numRegisters; i++) {
            Canvas::uniformVF(_activeProgram->constantID(firstRegister + i), data + i * 16, 16);
        }
    }

    void Context3D::setProgramConstantsFromByteArray(const String &programType, sInt firstRegister, sInt numRegisters, const Pointer<utils::ByteArray> &data, uInt byteArrayOffset) {
        setProgramConstantsFromBytes(programType, firstRegister, numRegisters, data->source() + byteArrayOffset);
    }

    void Context3D::setProgramConstantsFromMatrix(const String &programType, sInt firstRegister, const Pointer<geometry::Matrix3D> &data, bool transposedMatrix) {
        Canvas::uniformMatrixVF(_activeProgram->constantID(firstRegister), (const sByte *)data->rawData->source(), 64);
    }

    void Context3D::setProgramConstantsFromVector(const String &programType, sInt firstRegister, const Pointer<Vector<float>> &data, sInt numRegisters) {
        if (numRegisters == -1) numRegisters = data->length() / 4;
        setProgramConstantsFromBytes(programType, firstRegister, numRegisters, (const sByte *)data->source());
    }

    void Context3D::setRenderToBackBuffer() {
        _renderTarget = nullptr;
        runtime::Canvas::bindFrameBuffer(BufferTarget::FRAME_BUFFER, -1);
        runtime::Canvas::viewport(0, 0, _width, _height);
    }

    void Context3D::setRenderToTexture(const Pointer<Texture3D> &texture, bool enableDepthAndStencil, sInt antiAlias, sInt surfaceSelector, sInt colorOutputIndex) {
        _renderTarget = texture;
        runtime::Canvas::bindFrameBuffer(BufferTarget::FRAME_BUFFER, _renderTarget->frameBufferID());
        runtime::Canvas::viewport(0, 0, texture->width(), texture->height());
    }

    void Context3D::setSamplerStateAt(uInt sampler, const String &wrapMode, const String &texFilter, const String &mipFilter) {
        // empty
    }

    void Context3D::setScissorRectangle(const Pointer<geometry::Rectangle> &rectangle) {
        if (rectangle == nullptr) {
            Canvas::disable(ContextCapability::SCISSOR_TEST);
        } else {
            Canvas::enable(ContextCapability::SCISSOR_TEST);
            Canvas::scissor(
                runtime::Number::castFloat64(rectangle->x),
                runtime::Number::castFloat64(rectangle->y),
                runtime::Number::castFloat64(rectangle->width),
                runtime::Number::castFloat64(rectangle->height)
            );
        }
    }

    void Context3D::setStencilActions(const String &triangleFace, const String &compareMode, const String &actionOnBothPass, const String &actionOnDepthFail, const String &actionOnDepthPassStencilFail) {
        // empty
    }

    void Context3D::setStencilReferenceValue(const uInt reference, const uInt readMask, const uInt writeMask) {
        // empty
    }

    void Context3D::setTextureAt(uInt sampler, const Pointer<Texture3D> &texture) {
        Canvas::activeTexture((Canvas::TextureUnit)((sInt)Canvas::TextureUnit::TEXTURE0 + sampler));
        Canvas::bindTexture(Canvas::TextureTarget::TEXTURE_2D, texture->textureID());
        Canvas::uniform1I(_activeProgram->samplerID(sampler), sampler);

        Canvas::texParameterI(Canvas::TextureTarget::TEXTURE_2D, Canvas::TextureParameter::MAG_FILTER, (sInt)Canvas::TextureFilter::NEAREST);
        Canvas::texParameterI(Canvas::TextureTarget::TEXTURE_2D, Canvas::TextureParameter::MIN_FILTER, (sInt)Canvas::TextureFilter::NEAREST);
        Canvas::texParameterI(Canvas::TextureTarget::TEXTURE_2D, Canvas::TextureParameter::WRAP_S, (sInt)Canvas::TextureWrapMode::REPEAT);
        Canvas::texParameterI(Canvas::TextureTarget::TEXTURE_2D, Canvas::TextureParameter::WRAP_T, (sInt)Canvas::TextureWrapMode::REPEAT);
    }

    void Context3D::setVertexBufferAt(uInt index, const Pointer<VertexBuffer3D> &vertexBuffer, uInt bufferOffset, const String &format) {
        Canvas::bindBuffer(Canvas::BufferTarget::ARRAY_BUFFER, vertexBuffer->bufferID());
        Canvas::enableVertexAttribArray(_activeProgram->registerID(index));
        Canvas::vertexAttribPointer(_activeProgram->registerID(index), Context3DVertexBufferFormat::translateSize(format), Context3DVertexBufferFormat::translateType(format), vertexBuffer->data32PerVertex() * 4, bufferOffset * 4);
    }
}
