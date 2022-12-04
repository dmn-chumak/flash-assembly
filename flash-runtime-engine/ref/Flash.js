function Flash() {
    let _runtime = null;

    this.isContextAvailable = function() {
        return (
               window['WebAssembly'] != null
            && window['WebGLRenderingContext'] != null
            && window['AudioContext'] != null
        );
    };

    this.compose = function(source, stage, width, height) {
        if (_runtime == null) {
            _runtime = new FlashRuntime(
                source, {
                    canvas:     new FlashCanvas(stage, width, height),
                    clock:      new FlashClock(),
                    console:    new FlashConsole(),
                    keyboard:   new FlashKeyboard(),
                    math:       new FlashMath(),
                    memory:     new FlashMemory(),
                    mouse:      new FlashMouse(),
                    network:    new FlashNetwork(),
                    number:     new FlashNumber(),
                    sound:      new FlashSound()
                }
            );
            _runtime.compose();
        }
    };
    this.dispose = function() {
        if (_runtime != null) {
            _runtime.dispose();
            _runtime = null;
        }
    };
    this.runtime = function() {
        return _runtime;
    };

    return this;
}
