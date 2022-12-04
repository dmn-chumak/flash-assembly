function FlashRuntime(source, modules) {
    let _heapMemory = null;
    let _heapBuffer = null;

    let _runtimeImports = { };
    let _runtimeExports = { };
    let _runtimeDecoder = new TextDecoder('UTF-16');
    let _runtimeTable = null;
    let _runtimeTimer = 0;
    let _runtimeCanvas = null;

    let limit = 2500;

    function stageUpdateHandler(event) {
        let start = performance.now();

        try {
            _runtimeExports.stageUpdateHandler(event);
            _runtimeTimer = window.requestAnimationFrame(stageUpdateHandler, _runtimeCanvas);
        } catch (error) {
            console.log(error);
        }

        //document.getElementById('stats').innerHTML = '#' + limit + ' tiles: ~' + (performance.now() - start).toFixed(2) + ' ms';
        document.getElementById('stats').innerHTML = (
            'UpdateTime: ~' + (performance.now() - start).toFixed(2) + ' ms | HeapMemory: '
            + _runtimeExports.heapEmptyBlocks() + ' / '
            + _runtimeExports.heapTotalBlocks() + ' blocks '
            + ' [ used ' + _runtimeExports.heapCapacity() / 1024 + ' Kb'
            + ' / alloc ' + modules.memory.pages() * 64 + ' Kb ]'
        );
    }
    function stageContextHandler(event) {
        event.preventDefault();
    }
    function stageFocusHandler(event) {
        _runtimeExports.stageFocusHandler();
    }
    function stageBlurHandler(event) {
        _runtimeExports.stageBlurHandler();
    }
    function stageResizeHandler(event) {
        _runtimeExports.stageResizeHandler(event.width, event.height);
    }

    function mouseDownHandler(event) {
        _runtimeExports.mouseDownHandler(event.button);
        limit += 100;
    }
    function mouseUpHandler(event) {
        _runtimeExports.mouseUpHandler(event.button);
    }
    function mouseMoveHandler(event) {
        _runtimeExports.mouseMoveHandler(event.layerX, event.layerY);
    }
    function mouseWheelHandler(event) {
        _runtimeExports.mouseWheelHandler(event.deltaY);
    }

    function keyboardDownHandler(event) {
        _runtimeExports.keyboardDownHandler(event.which);
    }
    function keyboardUpHandler(event) {
        _runtimeExports.keyboardUpHandler(event.which);
    }

    function sourceLoadedHandler(event) {
        if (event.status != 200 || event.ok == false) {
            console.log('Flash source loading error.');
        } else {
            console.log('Flash source loaded:', event);
            return event.arrayBuffer();
        }
    }
    function sourceDecodedHandler(event) {
        console.log('Flash source decode handler:', event, _runtimeImports);
        return WebAssembly.instantiate(
            event, {
                env: _runtimeImports
            }
        );
    }
    function sourceCompiledHandler(event) {
        console.log('Flash source compile handler:', event);

        _runtimeExports = event.instance.exports;
        _heapMemory = _runtimeExports.memory;
        _heapBuffer = _runtimeExports.memory.buffer;
        _runtimeTable = _runtimeExports.table;
        _runtimeCanvas = modules.canvas.context();

        _runtimeExports.stageStartupHandler(
            new Int32Array(
                _heapBuffer,
                Int32Array.BYTES_PER_ELEMENT,
                Int32Array.BYTES_PER_ELEMENT
            )[0]
        );

        setTimeout(appendListeners, 100);
    }
    function sourceErrorHandler(error) {
        console.log('Flash source compose error:', error);
    }

    function appendListeners() {
        _runtimeCanvas.addEventListener(FlashEventType.CONTEXT_MENU, stageContextHandler);

        window.addEventListener(FlashEventType.WINDOW_FOCUS, stageFocusHandler, { passive: true });
        window.addEventListener(FlashEventType.WINDOW_BLUR, stageBlurHandler, { passive: true });
        window.addEventListener(FlashEventType.WINDOW_RESIZE, stageResizeHandler, { passive: true });

        _runtimeCanvas.addEventListener(FlashEventType.MOUSE_DOWN, mouseDownHandler, { passive: true });
        _runtimeCanvas.addEventListener(FlashEventType.MOUSE_UP, mouseUpHandler, { passive: true });
        _runtimeCanvas.addEventListener(FlashEventType.MOUSE_MOVE, mouseMoveHandler, { passive: true });
        _runtimeCanvas.addEventListener(FlashEventType.MOUSE_WHEEL, mouseWheelHandler, { passive: true });

        window.addEventListener(FlashEventType.KEY_DOWN, keyboardDownHandler, { passive: true });
        window.addEventListener(FlashEventType.KEY_UP, keyboardUpHandler, { passive: true });

        _runtimeTimer = window.requestAnimationFrame(stageUpdateHandler, _runtimeCanvas);
    }
    function removeListeners() {
        window.removeEventListener(FlashEventType.CONTEXT_MENU, stageContextHandler);
        window.removeEventListener(FlashEventType.WINDOW_FOCUS, stageFocusHandler);
        window.removeEventListener(FlashEventType.WINDOW_BLUR, stageBlurHandler);
        window.removeEventListener(FlashEventType.WINDOW_RESIZE, stageResizeHandler);

        _runtimeCanvas.removeEventListener(FlashEventType.MOUSE_DOWN, mouseDownHandler);
        _runtimeCanvas.removeEventListener(FlashEventType.MOUSE_UP, mouseUpHandler);
        _runtimeCanvas.removeEventListener(FlashEventType.MOUSE_MOVE, mouseMoveHandler);
        _runtimeCanvas.removeEventListener(FlashEventType.MOUSE_WHEEL, mouseWheelHandler);

        window.removeEventListener(FlashEventType.KEY_DOWN, keyboardDownHandler);
        window.removeEventListener(FlashEventType.KEY_UP, keyboardUpHandler);

        window.cancelAnimationFrame(_runtimeTimer);
    }
    function requestSource() {
        window.fetch(source).then(
            // Step #1: Trying to load source
            sourceLoadedHandler
        ).then(
            // Step #2: Trying to decode source
            sourceDecodedHandler
        ).then(
            // Step #3: Trying to compile source
            sourceCompiledHandler
        ).catch(
            // Catching thrown errors
            sourceErrorHandler
        );
    }
    function composeModule(runtime) {
        for (let moduleName in modules) {
            let module = modules[moduleName];

            if (module.hasOwnProperty('compose')) {
                console.log('Flash module composed: ', module);
                module.compose(runtime);
            }

            for (let method in module) {
                if (method != 'compose' && method != 'dispose') {
                    _runtimeImports[method] = module[method];
                }
            }
        }
    }
    function disposeModule() {
        for (let moduleName in modules) {
            let module = modules[moduleName];

            if (module.hasOwnProperty('dispose')) {
                console.log('Flash module disposed: ', module);
                module.dispose();
            }
        }
    }

    this.growMemory = function(pages) {
        _heapMemory.grow(pages);
        _heapBuffer = _heapMemory.buffer;
    };
    this.readBuffer = function(pointerType, pointer, length) {
        return new pointerType(_heapBuffer, pointer, length);
    };
    this.readSource = function(pointer, length) {
        return _heapBuffer.slice(pointer, pointer + length);
    };
    this.readString = function(pointer, length) {
        return _runtimeDecoder.decode(
            this.readBuffer(Int16Array, pointer, length)
        );
    };
    this.readHandle = function(pointer) {
        return _runtimeTable.get(pointer);
    };
    this.readModule = function(name) {
        return modules[name];
    };

    this.compose = function() {
        composeModule(this);
        requestSource();
    };
    this.dispose = function() {
        disposeModule();
    };

    return this;
}
