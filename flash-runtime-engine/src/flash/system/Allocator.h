#ifndef FLASH_SYSTEM_ALLOCATOR_H
#define FLASH_SYSTEM_ALLOCATOR_H

#include <flash/core/Type.h>

void operator delete[](link pointer);
void operator delete(link pointer);

link operator new[](heap capacity);
link operator new(heap capacity);

#endif
