#ifndef FLASH_RUNTIME_MEMORY_H
#define FLASH_RUNTIME_MEMORY_H

#include <flash/core/External.h>
#include <flash/core/Type.h>

namespace flash::runtime::Memory {
    imports void growMemory(const sInt pages);
    imports void statMemory(const sInt totalBlocks, const sInt emptyBlocks);
    imports void showMemory();
}

#endif
