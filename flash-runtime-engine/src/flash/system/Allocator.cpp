#include <flash/system/Allocator.h>
#include <flash/system/Memory.h>

void operator delete[](link pointer) {
    flash::system::Memory::heapRelease(pointer);
}

void operator delete(link pointer) {
    flash::system::Memory::heapRelease(pointer);
}

link operator new[](heap capacity) {
    return flash::system::Memory::heapAllocate(capacity);
}

link operator new(heap capacity) {
    return flash::system::Memory::heapAllocate(capacity);
}
