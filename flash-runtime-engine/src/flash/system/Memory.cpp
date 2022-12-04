#include <flash/runtime/Memory.h>
#include <flash/system/Memory.h>
#include <flash/runtime/Console.h>

namespace flash::system::Memory {
    const sChar S_1 = (sChar)'1';
    const sChar S_2 = (sChar)'2';
    const sChar S_3 = (sChar)'3';
    const sChar S_4 = (sChar)'4';
    const sChar S_5 = (sChar)'5';
    const sChar S_6 = (sChar)'6';
    const sChar S_7 = (sChar)'7';
    const sChar S_8 = (sChar)'8';
    const sChar S_9 = (sChar)'9';
    const sChar S_0 = (sChar)'0';

    struct Block {
        Block  *prevBlock;
        Block  *nextBlock;
        heap    size;
        bool    free;
    };

    static const heap HEAP_PAGE_SIZE    = 65536;
    static const heap BLOCK_SIZE        = sizeof(Block);
    static const heap ALIGN_SIZE        = sizeof(heap);

    static Block *heapBlock     = nullptr;
    static Block *lastBlock     = nullptr;

    static sInt allocatedPages  = 1;
    static sInt allocatedBlocks = 0;
    static sInt freeBlocks      = 0;

    /**
     * Calculates location of next memory block
     * @param block Position of current block
     * @param capacity Capacity of current block
     */
    inline Block *findNextBlock(Block *block, heap capacity) {
        return (Block *)((heap)block + BLOCK_SIZE + capacity);
    }

    /**
     * Calculates position of data for current block
     * @param block Position of current block
     */
    inline link findDataByBlock(Block *block) {
        return (link)((heap)block + BLOCK_SIZE);
    }

    /**
     * Calculates position of block for current data
     * @param pointer Position of current data
     */
    inline Block *findBlockByData(link pointer) {
        return (Block *)((heap)pointer - BLOCK_SIZE);
    }

    /**
     * Compose WebAssembly memory heap
     * @param offset Offset from zero to memory heap
     */
    void heapCompose(heap offset) {
        heapBlock = (Block *)offset;

        //-------------------------

        heapBlock->prevBlock = nullptr;
        heapBlock->nextBlock = nullptr;
        heapBlock->size = 0;
        heapBlock->free = true;

        //-------------------------

        lastBlock = (Block *)offset;
    }

    /**
     * Grows heap if last block has no enough memory
     * @param capacity Capacity of next block
     */
    void heapIncrease(heap capacity) {
        const heap nextLastBlock = (heap)findNextBlock(lastBlock, capacity);
        const sInt nextLastBlockPage = nextLastBlock / HEAP_PAGE_SIZE + 1;
        const sInt pagesToAllocate = nextLastBlockPage - allocatedPages + 5;

        if (pagesToAllocate > 0) {
            runtime::Memory::growMemory(pagesToAllocate);
            allocatedPages += pagesToAllocate;
        }
    }

    /**
     * Simple WebAssembly memory allocation
     * @param capacity Amount of memory needed to allocate
     *
     * 1. Align size of allocated blocks
     *
     * 2. Try to found next free block
     *
     * 3. If there are no any free block found
     *      3.1. Grow heap memory size if needed
     *      3.2. Allocate memory at end of heap
     *      3.3. Describe information about new end of heap
     *      3.4. Describe information about free memory block
     *      3.5. Increase allocated blocks counter
     *
     * 4. If there are large free block found
     *      4.1. Split large memory block into two pieces
     *      4.2. Describe information about free memory block piece
     *      4.3. Describe information about used memory block piece
     *      4.4. Increase allocated blocks counter
     *
     * 5. Otherwise use found free block
     *
     * 6. Return pointer to allocated data
     */
    link heapAllocate(heap capacity) {
        Block *freeBlock = lastBlock->prevBlock;
        Block *tempBlock = nullptr;

        //-------------------------

        // Step #1
        const uInt alignDelta = (capacity + BLOCK_SIZE) % ALIGN_SIZE;
        if (alignDelta != 0) {
            capacity += ALIGN_SIZE - alignDelta;
        }

        //-------------------------

        // Step #2
        while (freeBlock != nullptr) {
            if (freeBlock->size < capacity
            || !freeBlock->free) {
                freeBlock = freeBlock->prevBlock;
            } else {
                break;
            }
        }

        //-------------------------

        if (freeBlock == nullptr) {
            // Step #3.1
            heapIncrease(capacity);

            // Step #3.2
            freeBlock = lastBlock;

            // Step #3.3
            lastBlock = findNextBlock(freeBlock, capacity);
            lastBlock->prevBlock = freeBlock;
            lastBlock->nextBlock = nullptr;
            lastBlock->size = 0;
            lastBlock->free = true;

            // Step #3.3
            freeBlock->nextBlock = lastBlock;
            freeBlock->size = capacity;
            freeBlock->free = false;

            // Step #3.4
            allocatedBlocks++;
        } else if (freeBlock->size > BLOCK_SIZE + capacity) {
            // Step #4.1
            tempBlock = findNextBlock(freeBlock, capacity);

            // Step #4.2
            tempBlock->prevBlock = freeBlock;
            tempBlock->nextBlock = freeBlock->nextBlock;
            tempBlock->size = freeBlock->size - BLOCK_SIZE - capacity;
            tempBlock->free = true;

            // Step #4.3
            freeBlock->nextBlock->prevBlock = tempBlock;
            freeBlock->nextBlock = tempBlock;
            freeBlock->size = capacity;
            freeBlock->free = false;

            // Step 4.4
            allocatedBlocks++;
        } else {
            // Step #5
            freeBlock->free = false;
            freeBlocks--;
        }

        //-------------------------

        // Step #6
        return findDataByBlock(freeBlock);
    }

    /**
     * Simple WebAssembly memory release
     * @param pointer Pointer to memory needed to release
     *
     * 1. If current block next to end of heap
     *      1.1. Check previous blocks for emptiness
     *      1.2. Move last block to reduce heap size
     *      1.3. Return control to caller function
     *
     * 2. Otherwise mark it as free block
     *
     * 3. If next block is free, join two blocks into one
     *
     * 4. If prev block is free, join two blocks into one
     */
    void heapRelease(link pointer) {
        Block *freeBlock = findBlockByData(pointer);
        Block *tempBlock = nullptr;

        //-------------------------

        if (freeBlock->nextBlock == lastBlock) {
            // Step #1
            if (freeBlock->prevBlock != nullptr
            &&  freeBlock->prevBlock->free) {
                // Step #1.1
                freeBlock = freeBlock->prevBlock;
                allocatedBlocks--;
                freeBlocks--;
            }

            // Step #1.2
            lastBlock = freeBlock;
            lastBlock->nextBlock = nullptr;
            lastBlock->size = 0;
            lastBlock->free = true;

            // Step #1.3
            allocatedBlocks--;
            return;
        } else {
            // Step #2
            freeBlock->free = true;
            freeBlocks++;
        }

        //-------------------------

        if (freeBlock->nextBlock != nullptr
        &&  freeBlock->nextBlock->free) {
            // Step #3
            tempBlock = freeBlock->nextBlock;
            freeBlock->nextBlock = tempBlock->nextBlock;
            freeBlock->nextBlock->prevBlock = freeBlock;
            freeBlock->size += BLOCK_SIZE + tempBlock->size;
            allocatedBlocks--;
            freeBlocks--;
        }

        //-------------------------

        if (freeBlock->prevBlock != nullptr
        &&  freeBlock->prevBlock->free) {
            // Step #4
            tempBlock = freeBlock->prevBlock;
            tempBlock->nextBlock = freeBlock->nextBlock;
            tempBlock->nextBlock->prevBlock = tempBlock;
            tempBlock->size += BLOCK_SIZE + freeBlock->size;
            allocatedBlocks--;
            freeBlocks--;
        }
    }

    /**
     * Current WebAssembly amount of allocated memory blocks
     * @return Amount of allocated memory blocks
     */
    sInt heapTotalBlocks() {
        return allocatedBlocks;
    }

    /**
     * Current WebAssembly amount of empty memory blocks
     * @return Amount of empty memory blocks
     */
    sInt heapEmptyBlocks() {
        return freeBlocks;
    }

    /**
     * Current WebAssembly size of memory heap
     * @return Size of memory heap
     */
    heap heapCapacity() {
        return ((heap)lastBlock - (heap)heapBlock);
    }
}
