#ifndef SHOOTER_RENDER_GPU_RENDERER_H
#define SHOOTER_RENDER_GPU_RENDERER_H

#include <flash/display/BitmapData.h>
#include <flash/display/Stage.h>
#include <flash/display3D/Stage3D.h>
#include <flash/display3D/Context3D.h>
#include <flash/display3D/Context3DBlendFactor.h>
#include <flash/display3D/Context3DBufferUsage.h>
#include <flash/display3D/Context3DProgramType.h>
#include <flash/display3D/Context3DVertexBufferFormat.h>
#include <flash/display3D/IndexBuffer3D.h>
#include <flash/display3D/VertexBuffer3D.h>
#include <flash/events/ErrorEvent.h>
#include <flash/events/Event.h>
#include <flash/geometry/Matrix.h>
#include <flash/geometry/Matrix3D.h>
#include <flash/utils/ByteArray.h>
#include <shooter/render/common/GpuProgram.h>
#include <shooter/render/common/GpuTexture.h>
#include <shooter/render/common/GpuTextureRegion.h>
#include <shooter/utils/GeomUtils.h>
#include <flash/core/Core.h>
#include <shooter/render/DisplayObjectContainer.h>
#include <shooter/render/GpuRendererState.h>

using flash::display::BitmapData;
using flash::display::Stage;
using flash::display3D::Stage3D;
using flash::display3D::Context3D;
using flash::display3D::Context3DBlendFactor;
using flash::display3D::Context3DBufferUsage;
using flash::display3D::Context3DProgramType;
using flash::display3D::Context3DVertexBufferFormat;
using flash::display3D::IndexBuffer3D;
using flash::display3D::VertexBuffer3D;
using flash::events::ErrorEvent;
using flash::events::Event;
using flash::geometry::Matrix;
using flash::geometry::Matrix3D;
using flash::utils::ByteArray;
using shooter::render::common::GpuProgram;
using shooter::render::common::GpuTexture;
using shooter::render::common::GpuTextureRegion;
using shooter::utils::GeomUtils;

namespace shooter::render {
    class GpuRenderer : public DisplayObjectContainer, public  IRender {
        private:
            Pointer<Array<GpuRendererState>> _statesList;
            Pointer<GpuRendererState> _state;
            Pointer<Vector<float>> _vertexVector;
            uInt _vertexNumberMax;
            uInt _vertexNumber;
            Pointer<VertexBuffer3D> _vertexBuffer;
            Pointer<Vector<uShort>> _indexVector;
            uInt _indexNumberMax;
            uInt _indexNumber;
            Pointer<IndexBuffer3D> _indexBuffer;
            Pointer<Stage3D> _stage3D;
            Pointer<Context3D> _context3D;
            Pointer<Matrix3D> _matrix3D;
            Pointer<GpuProgram> _program;
            Pointer<GpuTexture> _texture;
            uInt _height;
            uInt _width;
            void prepareVertexes();
            void processVertexes();
        protected:
        public:
            GpuRenderer();
            GpuRenderer *GpuRendererConstruct();
            void requestContext(uInt width = uInt(800), uInt height = uInt(600));
            Pointer<GpuTexture> createTexture(Pointer<BitmapData> bitmap, Pointer<ByteArray> regions = nullptr);
            void renderTextureRegion(Pointer<GpuTextureRegion> region);
            void attachState(Pointer<DisplayObject> object);
            void detachState(Pointer<DisplayObject> object);
            void present();
            virtual ~GpuRenderer() override;
    };
}

#endif

