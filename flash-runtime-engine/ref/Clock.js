function FlashClock() {
    let _runtime = null;

    this.clockTimezoneOffset = function() {
        return new Date().getTimezoneOffset();
    };
    this.clockTime = function() {
        return new Date().getTime();
    };
    this.clockTimeout = function() {
        return performance.now();
    };

    this.compose = function(runtime) {
        _runtime = runtime;
    };
    this.dispose = function() {
        _runtime = null;
    };

    return this;
}
