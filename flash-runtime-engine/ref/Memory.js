function FlashMemory() {
    let _runtime = null;

    let _totalBlocks = 0;
    let _emptyBlocks = 0;
    let _pages = 1;

    this.growMemory = function(pages) {
        _runtime.growMemory(pages);
        _pages += pages;
    };
    this.statMemory = function(totalBlocks, emptyBlocks) {
        _totalBlocks = totalBlocks;
        _emptyBlocks = emptyBlocks;
    };
    this.showMemory = function() {
        console.log(
            "Flash memory usage: " + (_totalBlocks - _emptyBlocks) + "/" + _totalBlocks
            + " [" + _pages * 64 + " Kb]"
        );
    };

    this.compose = function(runtime) {
        _runtime = runtime;
    };
    this.dispose = function() {
        _runtime = null;
    };
    this.stats = function() {
        return (
            (_totalBlocks - _emptyBlocks) + "/" + _totalBlocks
            + " blocks [" + _pages * 64 + " Kb]"
        );
    };
    this.pages = function() {
        return _pages;
    };

    return this;
}
