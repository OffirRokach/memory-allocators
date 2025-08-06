#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include "../include/vsa.h"

#define MAGIC (0xFACE)
#define ISFREE(X) (X > 0)
#define ISALLOCED(X) (X < 0)
#define ABS(X) ((X < 0) ? (-X) : (X))
#define WORD_SIZE (sizeof(size_t))
#define HEAD_SIZE (sizeof(vsa_t))

struct vsa
{
    long block_size;
#ifndef NDEBUG
    size_t magic_num;
#endif
};

static vsa_t* NextBlock(vsa_t* vsa)
{
    assert(vsa->magic_num == MAGIC);
    
    return (vsa_t*)((char*)vsa + ABS(vsa->block_size) + HEAD_SIZE);

}

static void DefragmentMemory(vsa_t* vsa)
{
    vsa_t* ptr = vsa;
    long sum = 0;
    
    assert(ISFREE(vsa->block_size));

    while(ISFREE(ptr->block_size))
    {
        sum += ptr->block_size + HEAD_SIZE;
        ptr = NextBlock(ptr);
    }
    vsa->block_size = sum - HEAD_SIZE;
}

static size_t BlockAlignment(size_t block_size)
{
    return (block_size + WORD_SIZE-1) & ~(WORD_SIZE-1); 
}

vsa_t* VSAInit(void* memory, size_t memory_size)
{
    vsa_t* vsa = (vsa_t*)memory;
    vsa_t* last_header = (vsa_t*)((char*)memory + memory_size - HEAD_SIZE);
    if((2 * sizeof(vsa_t) >= memory_size)) 
    {
        return NULL;
    }
    vsa->block_size = memory_size - 2 * HEAD_SIZE;
    last_header->block_size = 0;
#ifndef NDEBUG
    vsa->magic_num = MAGIC;
    last_header->magic_num = MAGIC;
#endif
    return vsa;
}

void* VSAAlloc(vsa_t* vsa, size_t alloc_size)
{
    size_t temp;

    assert(alloc_size);

    if(alloc_size % WORD_SIZE != 0)
    {
        alloc_size = BlockAlignment(alloc_size);
    }

    while(vsa->block_size != 0)
    {
        if(ISFREE(vsa->block_size))
        {
            DefragmentMemory(vsa);
            if(vsa->block_size >= (long)alloc_size + HEAD_SIZE + WORD_SIZE)
            {
                temp = vsa->block_size - alloc_size - HEAD_SIZE;
                vsa->block_size = -alloc_size;
                #ifndef NDEBUG
                    vsa->magic_num = MAGIC;
                #endif
                vsa = NextBlock(vsa);
                vsa->block_size = temp;
                #ifndef NDEBUG
                    vsa->magic_num = MAGIC;
                #endif
                return (char*)vsa -(long)alloc_size;
            }

            else if(vsa->block_size >= (long)alloc_size)
            {
                vsa->block_size = -(vsa->block_size);
                
                return (char*)vsa + 1;
            }                       
        }
        vsa = NextBlock(vsa);
    }
    return NULL;
}

void VSAFree(void* block)
{
    vsa_t* vsa = (vsa_t*)block - 1;

    assert(vsa->magic_num == MAGIC);
    assert(ISALLOCED(vsa->block_size));

    vsa->block_size = -(vsa->block_size);
}

size_t VSALargestChunkAvailable(vsa_t* vsa)
{
    long max_size = 0;

    while(vsa->block_size != 0)
    {
        if(ISFREE(vsa->block_size))
        {
            DefragmentMemory(vsa);
        }
        if(vsa->block_size > max_size)
        {
            max_size = vsa->block_size;
        }
        vsa = NextBlock(vsa);
    }
    return max_size;
}
