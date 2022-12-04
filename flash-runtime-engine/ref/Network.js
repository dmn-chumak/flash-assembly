function FlashNetwork() {
    let _runtime = null;
    let _loaders = [ ];
    let _sockets = [ ];

    const LoaderEventType = {
        HTTP_STATUS:    0,
        OPEN:           1,
        IO_ERROR:       2,
        COMPLETE:       3,
        PROGRESS:       4,
        SECURITY_ERROR: 5
    };

    const SocketEventType = {
        CONNECT:        0,
        CLOSE:          1,
        SOCKET_DATA:    2,
        IO_ERROR:       3
    };

    function FlashNetworkLoader(callback, instance) {
        let _bytesContentReader = null;
        let _bytesContentSource = null;
        let _bytesContentBuffer = null;
        let _bytesReceived = 0;
        let _bytesTotal = 0;

        let _loaderCallback = callback;
        let _loaderInstance = instance;
        let _dispose = false;

        function fetchStatusHandler(response) {
            _loaderCallback(_loaderInstance, LoaderEventType.HTTP_STATUS, response.status, response.redirect ? 1 : 0);

            if (response.ok) {
                _loaderCallback(_loaderInstance, LoaderEventType.OPEN, 0, 0);

                _bytesTotal = parseInt(response.headers.get('Content-Length'));
                _bytesContentSource = new ArrayBuffer(_bytesTotal);
                _bytesContentBuffer = new Int8Array(_bytesContentSource);

                _bytesContentReader = response.body.getReader();
                _bytesContentReader.read().then(fetchProgressHandler);
            } else {
                _loaderCallback(_loaderInstance, LoaderEventType.IO_ERROR, 0, 0);
            }
        }
        function fetchProgressHandler(response) {
            if (response.done) {
                _loaderCallback(_loaderInstance, LoaderEventType.COMPLETE, 0, 0);
                return;
            }

            if (_dispose) {
                return;
            }

            _bytesContentBuffer.set(response.value, _bytesReceived);
            _bytesReceived += response.value.length;
            _loaderCallback(_loaderInstance, LoaderEventType.PROGRESS, _bytesReceived, _bytesTotal);

            _bytesContentReader.read().then(fetchProgressHandler);
        }
        function fetchFailedHandler(response) {
            _loaderCallback(_loaderInstance, LoaderEventType.SECURITY_ERROR, 0, 0);
        }

        this.composeSource = function(source) {
            window.fetch(source).then(
                fetchStatusHandler
            ).catch(
                fetchFailedHandler
            );
        };
        this.disposeSource = function() {
            _dispose = true;
        };
        this.content = function() {
            return _bytesContentBuffer;
        };

        return this;
    }

    function FlashSocket(callback, instance) {
        let _socketData = null;

        let _socketCallback = callback;
        let _socketInstance = instance;
        let _socket = null;

        function socketErrorHandler(response) {
            _socketCallback(_socketInstance, SocketEventType.IO_ERROR, 0);
            _socket = null;
        }
        function socketOpenHandler(response) {
            _socketCallback(_socketInstance, SocketEventType.CONNECT, 0);
        }
        function socketMessageHandler(response) {
            _socketData = new Int8Array(response.data);
            _socketCallback(_socketInstance, SocketEventType.SOCKET_DATA, response.data.byteLength);
        }
        function socketCloseHandler(response) {
            _socketCallback(_socketInstance, SocketEventType.CLOSE, response.code);
            _socket = null;
        }

        this.composeSource = function(address, port) {
            if (_socket == null) {
                _socket = new WebSocket('ws://' + address + ':' + port);

                _socket.onerror = socketErrorHandler;
                _socket.onopen = socketOpenHandler;
                _socket.onmessage = socketMessageHandler;
                _socket.onclose = socketCloseHandler;

                _socket.binaryType = 'arraybuffer';
            }
        };
        this.disposeSource = function() {
            if (_socket != null) {
                _socket.close();
                _socket = null;
            }
        };
        this.forwardSource = function(buffer) {
            if (_socket != null) {
                _socket.send(buffer);
            }
        };
        this.content = function() {
            return _socketData;
        };

        return this;
    }

    this.createLoader = function(loaderCallbackPtr, loaderPtr) {
        return _loaders.push(new FlashNetworkLoader(_runtime.readHandle(loaderCallbackPtr), loaderPtr)) - 1;
    };
    this.deleteLoader = function(loaderID) {
        _loaders[loaderID] = null;
    };
    this.startLoadingSource = function(loaderID, sourcePtr, sourceLen) {
        _loaders[loaderID].composeSource(_runtime.readString(sourcePtr, sourceLen));
    };
    this.stopLoadingSource = function(loaderID) {
        _loaders[loaderID].disposeSource();
    };
    this.bindLoadedData = function(loaderID, bufferPtr, bufferLen) {
        _runtime.readBuffer(Int8Array, bufferPtr, bufferLen).set(
            _loaders[loaderID].content()
        );
    };

    this.createSocket = function(socketCallbackPtr, socketPtr) {
        return _sockets.push(new FlashSocket(_runtime.readHandle(socketCallbackPtr), socketPtr)) - 1;
    };
    this.deleteSocket = function(socketID) {
        _sockets[socketID].disposeSource();
        _sockets[socketID] = null;
    };
    this.openSocketConnection = function(socketID, sourcePtr, sourceLen, portNumber) {
        _sockets[socketID].composeSource(_runtime.readString(sourcePtr, sourceLen), portNumber);
    };
    this.sendSocketData = function(socketID, bufferPtr, bufferLen) {
        _sockets[socketID].forwardSource(_runtime.readBuffer(Int8Array, bufferPtr, bufferLen));
    };
    this.closeSocketConnection = function(socketID) {
        _sockets[socketID].disposeSource();
    };
    this.bindSocketData = function(socketID, bufferPtr, bufferLen) {
        _runtime.readBuffer(Int8Array, bufferPtr, bufferLen).set(
            _sockets[socketID].content()
        );
    };

    this.compose = function(runtime) {
        _runtime = runtime;
    };
    this.dispose = function() {
        // empty
    };

    return this;
}
