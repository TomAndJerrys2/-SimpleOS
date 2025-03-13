// -- Memory library --
// -- FOR COFFEE OS --

#include "memory.h"

// Allocation pre-definitions
#define _BIT_SIZE_ 1024 * 1024
#define _MAX_ALLOC_ 20
static unsigned char memory[_BIT_SIZE_];

// heap base and addr
static int g_allocNum;
static int g_heapBaseAddr;

typedef struct _alloc_info_ {
    int address;
    unsigned int size;
} AllocateInfo;

AllocateInfo metaData[_MAX_ALLOC_] = { 0 };
