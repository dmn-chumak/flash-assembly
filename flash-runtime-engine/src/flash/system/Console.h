#ifndef FLASH_SYSTEM_CONSOLE_H
#define FLASH_SYSTEM_CONSOLE_H

#include <flash/core/String.h>
#include <flash/core/Type.h>

namespace flash::system::Console {
    void logMessage(const String &string);
    void logInformation(const String &string);
    void logWarning(const String &string);
    void logError(const String &string);
    void logStackTrace();
}

#endif
