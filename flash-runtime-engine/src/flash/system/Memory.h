#ifndef FLASH_SYSTEM_MEMORY_H
#define FLASH_SYSTEM_MEMORY_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::system::Memory {
    exports void heapCompose(heap offset);

    exports void heapIncrease(heap capacity);
    exports link heapAllocate(heap capacity);
    exports void heapRelease(link pointer);

    exports sInt heapTotalBlocks();
    exports sInt heapEmptyBlocks();
    exports heap heapCapacity();
}

#endif
