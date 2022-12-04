#include <flash/runtime/Console.h>
#include <flash/system/Console.h>

namespace flash::system::Console {
    void logMessage(const String &string) {
        runtime::Console::logMessage(string.source(), string.length());
    }

    void logInformation(const String &string) {
        runtime::Console::logInformation(string.source(), string.length());
    }

    void logWarning(const String &string) {
        runtime::Console::logWarning(string.source(), string.length());
    }

    void logError(const String &string) {
        runtime::Console::logError(string.source(), string.length());
    }

    void logStackTrace() {
        runtime::Console::logStackTrace();
    }
}
