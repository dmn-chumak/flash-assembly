#ifndef FLASH_RUNTIME_CONSOLE_H
#define FLASH_RUNTIME_CONSOLE_H

#include <flash/core/External.h>
#include <flash/core/String.h>

namespace flash::runtime::Console {
    imports void logMessage(const sChar *string, const heap length);
    imports void logInformation(const sChar *string, const heap length);
    imports void logWarning(const sChar *string, const heap length);
    imports void logError(const sChar *string, const heap length);
    imports void logStackTrace();
}

#endif
