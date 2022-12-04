function FlashConsole() {
    let _runtime = null;

    this.logMessage = function(stringPtr, stringLen) {
        console.log(_runtime.readString(stringPtr, stringLen));
    };
    this.logInformation = function(stringPtr, stringLen) {
        console.info(_runtime.readString(stringPtr, stringLen));
    };
    this.logWarning = function(stringPtr, stringLen) {
        console.warn(_runtime.readString(stringPtr, stringLen));
    };
    this.logError = function(stringPtr, stringLen) {
        console.error(_runtime.readString(stringPtr, stringLen));
    };
    this.logStackTrace = function() {
        console.trace();
    };

    this.compose = function(runtime) {
        _runtime = runtime;
    };
    this.dispose = function() {
        _runtime = null;
    };

    return this;
}
