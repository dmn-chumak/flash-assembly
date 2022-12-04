#ifndef FLASH_RUNTIME_CANVAS_H
#define FLASH_RUNTIME_CANVAS_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Canvas {
    enum class BufferTarget : sInt {
        ARRAY_BUFFER                = 0x8892,
        ELEMENT_ARRAY_BUFFER        = 0x8893,
        FRAME_BUFFER                = 0x8D40,
        RENDER_BUFFER               = 0x8D41
    };

    enum class BufferUsage : sInt {
        STREAM_DRAW                 = 0x88E0,
        STATIC_DRAW                 = 0x88E4,
        DYNAMIC_DRAW                = 0x88E8
    };

    enum class BufferAttachment : sInt {
        COLOR_ATTACHMENT            = 0x8CE0,
        DEPTH_ATTACHMENT            = 0x8D00,
        DEPTH_STENCIL_ATTACHMENT    = 0x8D20,
        STENCIL_ATTACHMENT          = 0x821A
    };

    enum class RenderBufferFormat : sInt {
        RGBA4                       = 0x8056,
        RGB5A1                      = 0x8057,
        RGB565                      = 0x8D62,
        DEPTH_COMPONENT16           = 0x81A5,
        STENCIL_INDEX8              = 0x8D48,
        DEPTH_STENCIL               = 0x84F9
    };

    enum class ProgramType : sInt {
        FRAGMENT_SHADER             = 0x8B30,
        VERTEX_SHADER               = 0x8B31
    };

    enum class TextureTarget : sInt {
        TEXTURE_2D                  = 0x0DE1,
        TEXTURE_CUBE_MAP            = 0x8513
    };

    enum class TextureUnit : sInt {
        TEXTURE0                    = 0x84C0,
        TEXTURE1                    = 0x84C1,
        TEXTURE2                    = 0x84C2,
        TEXTURE3                    = 0x84C3,
        TEXTURE4                    = 0x84C4,
        TEXTURE5                    = 0x84C5,
        TEXTURE6                    = 0x84C6,
        TEXTURE7                    = 0x84C7,
        TEXTURE8                    = 0x84C8,
        TEXTURE9                    = 0x84C9
    };

    enum class TextureParameter : sInt {
        MAG_FILTER                  = 0x2800,
        MIN_FILTER                  = 0x2801,
        WRAP_S                      = 0x2802,
        WRAP_T                      = 0x2803
    };

    enum class TextureFilter : sInt {
        LINEAR                      = 0x2600,
        NEAREST                     = 0x2601
    };

    enum class TextureMipFilter : sInt {
        NEAREST_MIPMAP_NEAREST      = 0x2700,
        LINEAR_MIPMAP_NEAREST       = 0x2701,
        NEAREST_MIPMAP_LINEAR       = 0x2702,
        LINEAR_MIPMAP_LINEAR        = 0x2703
    };

    enum class TextureWrapMode : sInt {
        REPEAT                      = 0x2901,
        CLAMP_TO_EDGE               = 0x812F,
        MIRRORED_REPEAT             = 0x8370
    };

    enum class CullingMode : sInt {
        FRONT                       = 0x0404,
        BACK                        = 0x0405,
        FRONT_AND_BACK              = 0x0408
    };

    enum class FaceDirection : sInt {
        CW                          = 0x0900,
        CCW                         = 0x0901
    };

    enum class BlendMode : sInt {
        FUNC_ADD                    = 0x8006,
        FUNC_SUBTRACT               = 0x800A,
        FUNC_REVERSE_SUBTRACT       = 0x800B
    };

    enum class BlendFactor : sInt {
        SRC_COLOR                   = 0x0300,
        ONE_MINUS_SRC_COLOR         = 0x0301,
        SRC_ALPHA                   = 0x0302,
        ONE_MINUS_SRC_ALPHA         = 0x0303,
        DST_ALPHA                   = 0x0304,
        ONE_MINUS_DST_ALPHA         = 0x0305,
        DST_COLOR                   = 0x0306,
        ONE_MINUS_DST_COLOR         = 0x0307,
        SRC_ALPHA_SATURATE          = 0x0308,
        CONSTANT_COLOR              = 0x8001,
        ONE_MINUS_CONSTANT_COLOR    = 0x8002,
        CONSTANT_ALPHA              = 0x8003,
        ONE_MINUS_CONSTANT_ALPHA    = 0x8004,
        ZERO                        = 0x0000,
        ONE                         = 0x0001
    };

    enum class CompareMode : sInt {
        NEVER                       = 0x0200,
        LESS                        = 0x0201,
        EQUAL                       = 0x0202,
        LEQUAL                      = 0x0203,
        GREATER                     = 0x0204,
        NOTEQUAL                    = 0x0205,
        GEQUAL                      = 0x0206,
        ALWAYS                      = 0x0207
    };

    enum class StencilAction : sInt {
        KEEP                        = 0x1E00,
        REPLACE                     = 0x1E01,
        INCR                        = 0x1E02,
        DECR                        = 0x1E03,
        INVERT                      = 0x150A,
        INCR_WRAP                   = 0x8507,
        DECR_WRAP                   = 0x8508,
        ZERO                        = 0x0000
    };

    enum class ContextCapability : sInt {
        BLEND                       = 0x0BE2,
        CULL_FACE                   = 0x0B44,
        DEPTH_TEST                  = 0x0B71,
        DITHER                      = 0x0BD0,
        SCISSOR_TEST                = 0x0C11,
        STENCIL_TEST                = 0x0B90
    };

    enum class ClearMask : sInt {
        NONE                        = 0x0000,
        DEPTH                       = 0x0100,
        STENCIL                     = 0x0400,
        COLOR                       = 0x4000,
        ALL                         = 0x4500
    };

    enum class RenderMode : sInt {
        POINTS                      = 0x0000,
        LINES                       = 0x0001,
        LINE_LOOP                   = 0x0002,
        LINE_STRIP                  = 0x0003,
        TRIANGLES                   = 0x0004,
        TRIANGLE_STRIP              = 0x0005,
        TRIANGLE_FAN                = 0x0006
    };

    enum class DataType : sInt {
        BYTE                        = 0x1400,
        UNSIGNED_BYTE               = 0x1401,
        SHORT                       = 0x1402,
        UNSIGNED_SHORT              = 0x1403,
        INT                         = 0x1404,
        UNSIGNED_INT                = 0x1405,
        FLOAT                       = 0x1406
    };

    enum class PixelParameter : sInt {
        PACK_ALIGNMENT              = 0x0D05,
        UNPACK_ALIGNMENT            = 0x0CF5,
        UNPACK_FLIP_Y_WEBGL         = 0x9240
    };

    imports sInt createBuffer();
    imports void deleteBuffer(sInt bufferID);
    imports void bindBuffer(BufferTarget target, sInt bufferID);
    imports void bufferData(BufferTarget target, const sByte *bufferPtr, heap bufferLen, BufferUsage usage);
    imports void bufferSubData(BufferTarget target, heap offset, const sByte *bufferPtr, heap bufferLen);

    imports sInt createRenderBuffer();
    imports void deleteRenderBuffer(sInt bufferID);
    imports void bindRenderBuffer(BufferTarget target, sInt bufferID);
    imports void renderBufferStorage(BufferTarget target, RenderBufferFormat format, sInt width, sInt height);

    imports sInt createFrameBuffer();
    imports void deleteFrameBuffer(sInt bufferID);
    imports void bindFrameBuffer(BufferTarget target, sInt bufferID);
    imports sInt checkFrameBufferStatus(BufferTarget target);
    imports void frameBufferRenderBuffer(BufferTarget target, BufferAttachment attachment, BufferTarget bufferTarget, sInt bufferID);
    imports void frameBufferTexture2D(BufferTarget target, BufferAttachment attachment, TextureTarget textureTarget, sInt textureID, sInt mipLevel);
    // TODO: imports void readPixels(sInt x, sInt y, sInt width, sInt height, enum format, enum type, const sByte *bufferPtr, heap bufferLen);

    imports sInt createProgram();
    imports void deleteProgram(sInt programID);
    imports void validateProgram(sInt programID);
    imports void linkProgram(sInt programID);
    imports bool checkProgramStatus(sInt programID);
    imports void useProgram(sInt programID);

    imports sInt createShader(ProgramType type);
    imports void deleteShader(sInt shaderID);
    imports void shaderSource(sInt shaderID, const sChar *programPtr, heap programLen);
    imports void compileShader(sInt shaderID);
    imports void attachShader(sInt programID, sInt shaderID);
    imports void detachShader(sInt programID, sInt shaderID);
    imports bool checkShaderStatus(sInt shaderID);

    imports sInt createTexture();
    imports void deleteTexture(sInt textureID);
    imports void bindTexture(TextureTarget target, sInt textureID);
    imports void activeTexture(TextureUnit textureUnit);
    imports void copyTexImage2D(TextureTarget target, sInt mipLevel, sInt x, sInt y, sInt width, sInt height);
    imports void copyTexSubImage2D(TextureTarget target, sInt mipLevel, sInt offsetX, sInt offsetY, sInt x, sInt y, sInt width, sInt height);
    imports void texParameterI(TextureTarget target, TextureParameter parameter, sInt value);
    imports void texParameterF(TextureTarget target, TextureParameter parameter, double value);
    imports void texImage2D(TextureTarget target, sInt mipLevel, sInt width, sInt height, const sByte *bufferPtr, heap bufferLen);
    imports void texSubImage2D(TextureTarget target, sInt mipLevel, sInt offsetX, sInt offsetY, sInt width, sInt height, const sByte *bufferPtr, heap bufferLen);
    imports void generateMipmap(TextureTarget target);
    imports void pixelStoreI(PixelParameter param, sInt value);

    imports sInt getUniformLocation(sInt programID, const sChar *namePtr, heap nameLen);
    imports void uniform1I(sInt uniformID, sInt x);
    imports void uniform2I(sInt uniformID, sInt x, sInt y);
    imports void uniform3I(sInt uniformID, sInt x, sInt y, sInt z);
    imports void uniform4I(sInt uniformID, sInt x, sInt y, sInt z, sInt w);
    imports void uniformVI(sInt uniformID, const sByte *bufferPtr, sInt bufferLn);
    imports void uniform1F(sInt uniformID, double x);
    imports void uniform2F(sInt uniformID, double x, double y);
    imports void uniform3F(sInt uniformID, double x, double y, double z);
    imports void uniform4F(sInt uniformID, double x, double y, double z, double w);
    imports void uniformVF(sInt uniformID, const sByte *bufferPtr, sInt bufferLen);
    imports void uniformMatrixVF(sInt uniformID, const sByte *bufferPtr, sInt bufferLen);

    imports sInt getAttribLocation(sInt programID, const sChar *namePtr, heap nameLen);
    imports void vertexAttribPointer(sInt attributeID, sInt size, DataType type, sInt stride, sInt offset);
    imports void vertexAttrib1F(sInt attributeID, double x);
    imports void vertexAttrib2F(sInt attributeID, double x, double y);
    imports void vertexAttrib3F(sInt attributeID, double x, double y, double z);
    imports void vertexAttrib4F(sInt attributeID, double x, double y, double z, double w);
    imports void vertexAttribVF(sInt attributeID, const sByte *bufferPtr, sInt bufferLen);
    imports void enableVertexAttribArray(sInt attributeID);
    imports void disableVertexAttribArray(sInt attributeID);

    imports void cullFace(CullingMode cullingMode);
    imports void frontFace(FaceDirection faceDirection);

    imports void blendColor(double red, double green, double blue, double alpha);
    imports void blendEquation(BlendMode mode);
    imports void blendEquationSeparate(BlendMode modeRGB, BlendMode modeAlpha);
    imports void blendFunc(BlendFactor srcFactor, BlendFactor dstFactor);
    imports void blendFuncSeparate(BlendFactor srcFactorRGB, BlendFactor dstFactorRGB, BlendFactor srcFactorAlpha, BlendFactor dstFactorAlpha);

    imports void stencilFunc(CompareMode compareMode, sInt reference, sInt mask);
    imports void stencilFuncSeparate(CullingMode cullingMode, CompareMode compareMode, sInt reference, sInt mask);
    imports void stencilMask(sInt mask);
    imports void stencilMaskSeparate(CullingMode cullingMode, sInt mask);
    imports void stencilOp(StencilAction stencilFail, StencilAction depthFail, StencilAction bothPass);
    imports void stencilOpSeparate(CullingMode cullingMode, StencilAction stencilFail, StencilAction depthFail, StencilAction bothPass);

    imports void depthFunc(CompareMode compareMode);
    imports void depthMask(bool enable);
    imports void depthRange(double nearValue, double farValue);

    imports void scissor(sInt x, sInt y, sInt width, sInt height);
    imports void viewport(sInt x, sInt y, sInt width, sInt height);
    imports void clearColor(double red, double green, double blue, double alpha);
    imports void clearStencil(sInt stencil);
    imports void clearDepth(double depth);
    imports void colorMask(bool red, bool green, bool blue, bool alpha);
    imports void enable(ContextCapability capability);
    imports void disable(ContextCapability capability);
    imports void clear(ClearMask mask);
    imports void drawArrays(RenderMode renderMode, sInt first, sInt count);
    imports void drawElements(RenderMode renderMode, sInt count, DataType type, sInt offset);
    imports void finish();
    imports void flush();
}

#endif
