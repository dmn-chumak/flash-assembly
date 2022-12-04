#include <flash/display3D/Context3DVertexBufferFormat.h>

namespace flash::display3D {
    const sByte *Context3DVertexBufferFormat::BYTES_4  = "bytes4";
    const sByte *Context3DVertexBufferFormat::FLOAT_4  = "float4";
    const sByte *Context3DVertexBufferFormat::FLOAT_3  = "float3";
    const sByte *Context3DVertexBufferFormat::FLOAT_2  = "float2";
    const sByte *Context3DVertexBufferFormat::FLOAT_1  = "float1";

    runtime::Canvas::DataType Context3DVertexBufferFormat::translateType(const String &value) {
        if (value == BYTES_4)       return runtime::Canvas::DataType::SHORT;
        else if (value == FLOAT_4)  return runtime::Canvas::DataType::FLOAT;
        else if (value == FLOAT_3)  return runtime::Canvas::DataType::FLOAT;
        else if (value == FLOAT_2)  return runtime::Canvas::DataType::FLOAT;
        else if (value == FLOAT_1)  return runtime::Canvas::DataType::FLOAT;
        else                        return runtime::Canvas::DataType();
    };

    uInt Context3DVertexBufferFormat::translateSize(const String &value) {
        if (value == BYTES_4)       return 4;
        else if (value == FLOAT_4)  return 4;
        else if (value == FLOAT_3)  return 3;
        else if (value == FLOAT_2)  return 2;
        else if (value == FLOAT_1)  return 1;
        else                        return 0;
    }
}
