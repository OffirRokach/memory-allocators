#include <assert.h> /*assert*/
#include <stddef.h> /*size_t*/

#include "fsa.h" /*fsa funcs*/

#define WORD_SIZE (8)

struct fsa
{
    size_t next_free;
};

typedef struct block_meta_data block_t;


struct block_meta_data
{
    size_t next_free;
};

static size_t BlockAlignment(size_t block_size)
{
    return (block_size + WORD_SIZE-1) & ~(WORD_SIZE-1); 
}

size_t FSASuggestSize(size_t block_size, size_t n_blocks)
{
    size_t block_size_aligned = BlockAlignment(block_size);

    return (((sizeof(block_t) + block_size_aligned) * n_blocks) + sizeof(fsa_t));
}

fsa_t* FSAInit(void* memory, size_t block_size, size_t memory_size)
{
    fsa_t* fsa = NULL;
    block_t* block_metadata = NULL;
    size_t block_runner = 0;
    size_t big_block_size = BlockAlignment(block_size) + sizeof(block_t);
    size_t n_blocks = (memory_size - sizeof(fsa_t)) / big_block_size;

    assert(memory);
    assert(block_size < memory_size);
    assert(0 != memory_size);
    assert(0 != block_size);

    if(0 == n_blocks)
    {
        return NULL;
    }

    fsa = (fsa_t*)memory;
    fsa->next_free = sizeof(fsa_t);

    block_metadata = (block_t*)((char*)fsa + sizeof(fsa_t));

    for(block_runner = 0; block_runner <  n_blocks-1; ++block_runner)
    {
        block_metadata->next_free = fsa->next_free + (big_block_size * (block_runner + 1));
        block_metadata = (block_t*)((char*)fsa + block_metadata->next_free);
    }

    block_metadata->next_free = 0;

    return fsa;
}

void* FSAAlloc(fsa_t* fsa)
{
    block_t* block = NULL;

    assert(fsa);

    if (0 == fsa->next_free)
    {
        return NULL;
    }

    block = (block_t*)((char*)fsa + fsa->next_free);
    fsa->next_free = block->next_free;

     return (char*)block + sizeof(size_t);
}

void FSAFree(fsa_t* fsa, void* p_block)
{
    block_t* block = NULL;

    assert(p_block);
    assert(fsa);

    block = (block_t*)((char*)p_block - sizeof(size_t));
    block->next_free = fsa->next_free;
    fsa->next_free = (size_t)((char*)block - (char*)fsa);
}

size_t FSACountFree(const fsa_t* fsa)
{
    size_t count = 0;
    size_t next_free = 0;
    block_t* block = NULL;

    assert(fsa);

    next_free = fsa->next_free;

    while(0 != next_free)
    {
        block = (block_t*)((char*)fsa + next_free);
        next_free = block->next_free;
        ++count;
    }
    return count;
}
