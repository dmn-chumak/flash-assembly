#include <shooter/render/GpuRenderer.h>

namespace shooter::render {
    void GpuRenderer::prepareVertexes() {
        _vertexNumber = uInt(0);
        _indexNumber = uInt(0);
    }

    void GpuRenderer::processVertexes() {
        sInt idx = 0;
        sInt vtx = 0;
        if (_vertexNumber == Double(0)) {
            return;
        }
        if (_vertexNumber > _vertexNumberMax || _vertexBuffer == nullptr) {
            if (_vertexBuffer != nullptr) {
                _vertexBuffer->dispose();
                _indexBuffer->dispose();
            }
            for (idx = _indexNumberMax, vtx = _vertexNumberMax; idx < _indexNumber; idx += sInt(6), vtx += sInt(4)) {
                (*_indexVector.object())[idx + uInt(0)] = vtx + uInt(0);
                (*_indexVector.object())[idx + uInt(1)] = vtx + uInt(1);
                (*_indexVector.object())[idx + uInt(2)] = vtx + uInt(2);
                (*_indexVector.object())[idx + uInt(3)] = vtx + uInt(2);
                (*_indexVector.object())[idx + uInt(4)] = vtx + uInt(3);
                (*_indexVector.object())[idx + uInt(5)] = vtx + uInt(0);
            }
            _indexBuffer = _context3D->createIndexBuffer(_indexNumber);
            _indexBuffer->uploadFromVector(_indexVector, sInt(0), _indexNumber);
            _indexNumberMax = _indexNumber;
            _vertexBuffer = _context3D->createVertexBuffer(_vertexNumber, uInt(6), Context3DBufferUsage::DYNAMIC_DRAW);
            _vertexNumberMax = _vertexNumber;
        }
        _vertexBuffer->uploadFromVector(_vertexVector, sInt(0), _vertexNumber);
        if (_texture != nullptr) {
            _context3D->setTextureAt(uInt(0), _texture->parentGetter());
        } else {
            _context3D->setTextureAt(uInt(0), nullptr);
        }
        _context3D->setVertexBufferAt(uInt(0), _vertexBuffer, uInt(0), Context3DVertexBufferFormat::FLOAT_2);
        _context3D->setVertexBufferAt(uInt(1), _vertexBuffer, uInt(2), Context3DVertexBufferFormat::FLOAT_4);
        _context3D->drawTriangles(_indexBuffer, sInt(0), _indexNumber / sInt(3));
        _texture = nullptr;
    }

    GpuRenderer::GpuRenderer() {
        _statesList = nullptr;
        _state = nullptr;
        _vertexVector = nullptr;
        _vertexNumberMax = 0;
        _vertexNumber = 0;
        _vertexBuffer = nullptr;
        _indexVector = nullptr;
        _indexNumberMax = 0;
        _indexNumber = 0;
        _indexBuffer = nullptr;
        _stage3D = nullptr;
        _context3D = nullptr;
        _matrix3D = nullptr;
        _program = nullptr;
        _texture = nullptr;
        _height = 0;
        _width = 0;
    }

    GpuRenderer *GpuRenderer::GpuRendererConstruct() {
        DisplayObjectContainer::DisplayObjectContainerConstruct();
        _vertexVector = new Vector<float>();
        _vertexNumberMax = uInt(0);
        _vertexNumber = uInt(0);
        _indexVector = new Vector<uShort>();
        _indexNumberMax = uInt(0);
        _indexNumber = uInt(0);
        _statesList = new Array<GpuRendererState>();
        _state = (new GpuRendererState())->GpuRendererStateConstruct();
        return this;
    }

    void GpuRenderer::requestContext(uInt width, uInt height) {
        if (_stage3D != nullptr) {
            return;
        }
        _stage3D = new Stage3D(0);
        double w = 800;
        double h = 600;

        _width = width;
        _height = height;

        _context3D = _stage3D->requestContext3D();

        _context3D->configureBackBuffer(_width, _height,    (0), false);
        _matrix3D = new Matrix3D();
        _matrix3D->appendScale(Double(2) / w, -Double(2) / h, Double(1));
        _matrix3D->appendTranslation(-1, 1, 0);

        //_matrix3D->appendTranslation(-w / Double(2), -h / Double(2), Double(0));
        //_matrix3D->appendScale(Double(2) / w, -Double(2) / h, Double(1));

        _program = (new GpuProgram())->GpuProgramConstruct(
            _context3D,
            (
                "attribute   vec2 reg0;"
                "attribute   vec4 reg1;"
                "uniform     mat4 uni0;"
                "varying     vec2 var0;"

                "void main() {"
                    "gl_Position = uni0 * vec4(reg0.xy, 0, 1);"
                    "var0 = reg1.xy;"
                "}"
            ), (
                "precision mediump float;"
                "uniform sampler2D tex0;"
                "varying vec2 var0;"

                "void main() {"
                    "gl_FragColor = texture2D(tex0, var0);"
                "}"
            )
        );
    }

    Pointer<GpuTexture> GpuRenderer::createTexture(Pointer<BitmapData> bitmap, Pointer<ByteArray> regions) {
        return (new GpuTexture())->GpuTextureConstruct(_context3D, bitmap, regions);
    }

    void GpuRenderer::renderTextureRegion(Pointer<GpuTextureRegion> region) {
        Pointer<Vector<double>> vertex = nullptr;
        Pointer<Matrix> matrix = nullptr;
        sInt offset = 0;
        sInt i = 0;
        if (region->parentGetter() != _texture) {
            processVertexes();
            _texture = region->parentGetter();
            prepareVertexes();
        }
        vertex = region->vertexGetter();
        matrix = _state->matrix;
        offset = _vertexNumber * sInt(6);
        for (i = sInt(0); i < sInt(8); i += sInt(2)) {
            (*_vertexVector.object())[(uInt)offset++] = (matrix->a * vertex->obtainAt((uInt)i) + matrix->c * vertex->obtainAt((uInt)i + uInt(1)) + matrix->tx);
            (*_vertexVector.object())[(uInt)offset++] = (matrix->b * vertex->obtainAt((uInt)i) + matrix->d * vertex->obtainAt((uInt)i + uInt(1)) + matrix->ty);
            (*_vertexVector.object())[(uInt)offset++] = vertex->obtainAt((uInt)i + uInt(8));
            (*_vertexVector.object())[(uInt)offset++] = vertex->obtainAt((uInt)i + uInt(9));
            (*_vertexVector.object())[(uInt)offset++] = Float(1);
            (*_vertexVector.object())[(uInt)offset++] = Float(1);
        }
        _vertexNumber += uInt(4);
        _indexNumber += uInt(6);
    }

    void GpuRenderer::attachState(Pointer<DisplayObject> object) {
        Pointer<GpuRendererState> state = nullptr;
        if (GeomUtils::identity(object->matrixGetter())) {
            return;
        }
        state = (new GpuRendererState())->GpuRendererStateConstruct();
        state->object = object;
        GeomUtils::concat(state->matrix, _state->matrix, object->matrixGetter());
        _statesList->insertLast(_state);
        _state = state;
    }

    void GpuRenderer::detachState(Pointer<DisplayObject> object) {
        if (_state->object == object) {
            _state = _statesList->removeLast();
        }
    }

    void GpuRenderer::present() {
        if (_context3D == nullptr) {
            return;
        }
        _context3D->clear(Float(1), Float(1), Float(1), Float(1));
        _context3D->setProgramConstantsFromMatrix(Context3DProgramType::VERTEX, sInt(0), _matrix3D, true);
        _context3D->setBlendFactors(Context3DBlendFactor::ONE, Context3DBlendFactor::ONE_MINUS_SOURCE_ALPHA);
        _context3D->setProgram(_program->parentGetter());
        prepareVertexes();
        render(this);
        processVertexes();
        _context3D->present();
    }

    GpuRenderer::~GpuRenderer() {
    }
}

