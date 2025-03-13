// -- Memory library --
// -- FOR COFFEE OS --

#include <sys/mman.h>
#include <sys/resource.h>

#ifndef MEMORY_H_
#define MEMORY_H_

// Heap | Block Shifting
#define _HEAP_SHIFT(startptr) ((void*)startptr + sizeof(HEAP))
#define _BLOCK_SHIFT(startptr) ((void*)startptr + sizeof(BLOCK))

// Small Alloc Sizing for Heap | Block
#define _THEAP_ALLOC_SIZE_ (4 * getPageSize())
#define _TBLOCK_SIZE_ (_THEAP_ALLOC_SIZE_ / 128)
#define _SHEAP_ALLOC_SIZE_ (16 * getPageSize())
#define _SBLOCK_SIZE_ (_SHEAP_ALLOC_SIZE_ / 128)

// Memory functions
void* allocate(size_t allocSize); // like malloc - uninitialized
void* copyallocate(size_t allocSize); // like calloc - init to 0
void* reallocate(void* ptr, size_t newAllocSize); // like realloc
void* deallocate(void* ptr); // like free

// Mapping and unMapping Memory Addresses
const void mem_map(void memAddr, size_t length, int prot, 
    int flags, int fd, off_t offset);
const void mem_unmap(void memAddr, size_t length);

// limit memory calls
int getrLimit(int res, struct rLimit rlp);
int setrLimit(int res, const struct rLimit& rlp);

// Memory and Heap "objects"
typedef struct heap {
    struct heap* prev; // previous heap ptr
    struct heap* next; // next heap ptr

    heapGroup _group_;

    size_t totalSize; // size
    size_t availableSize; // size it can have
    size_t blockCount; // selfexpl
} HEAP;

typedef struct block {
    struct block* prev; // previous block ptr
    struct block* next; // next block ptr

    size_t dataSize; // size of the data stored
    int isFree; // if the block is free or NULL
} BLOCK;

// Custom Type
typedef struct _universal_type_ {
    struct _universal_type* data; // holds data thats allocated
    size_t type_size; // the size of the type i.e string, character etc
} Universal;

#endif