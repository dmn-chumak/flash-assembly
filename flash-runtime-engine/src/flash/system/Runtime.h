#ifndef FLASH_SYSTEM_RUNTIME_H
#define FLASH_SYSTEM_RUNTIME_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::system::Runtime {
    exports void stageStartupHandler(heap heapOffset);
    exports void stageUpdateHandler(uInt timeStamp);
    exports void stageFocusHandler();
    exports void stageBlurHandler();
    exports void stageResizeHandler(uInt stageWidth, uInt stageHeight);

    exports void mouseDownHandler(uByte mouseButton);
    exports void mouseUpHandler(uByte mouseButton);
    exports void mouseMoveHandler(sInt mouseX, sInt mouseY);
    exports void mouseWheelHandler(sInt wheelDelta);

    exports void keyboardDownHandler(uByte keyCode);
    exports void keyboardUpHandler(uByte keyCode);
}

#endif
