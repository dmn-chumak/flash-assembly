#include <flash/system/Runtime.h>
#include <flash/core/Core.h>
#include <shooter/Main.h>

using shooter::Main;

namespace flash::system::Runtime {
    Main *main = nullptr;

    void stageStartupHandler(heap heapOffset) {
        Memory::heapCompose(heapOffset);
        main = new Main();
    }

    void stageUpdateHandler(uInt timeStamp) {
        main->render();
    }

    void stageFocusHandler() {
        Console::logMessage("stageFocusHandler");
    }

    void stageBlurHandler() {
        Console::logMessage("stageBlurHandler");
    }

    void stageResizeHandler(uInt stageWidth, uInt stageHeight) {
        Console::logMessage(String() + "stageResizeHandler [stageWidth=" + Integer(stageWidth) + ", stageHeight=" + Integer(stageHeight) + "]");
    }

    void mouseDownHandler(uByte mouseButton) {
        // empty
    }

    void mouseUpHandler(uByte mouseButton) {
        // empty
    }

    void mouseMoveHandler(sInt mouseX, sInt mouseY) {
        // empty
    }

    void mouseWheelHandler(sInt wheelDelta) {
        // empty
    }

    void keyboardDownHandler(uByte keyCode) {
        // empty
    }

    void keyboardUpHandler(uByte keyCode) {
        // empty
    }
}
