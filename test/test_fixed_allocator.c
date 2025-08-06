#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "fsa.h"
#include "testing_macros.h"

/*test fsa when given aligned block_size*/

void TestFSASimple1() 
{
    size_t block_size = 32;
    size_t n_blocks = 5;
    fsa_t* fsa = NULL;
    size_t suggested_size = 0;
    void* block1 = NULL;
    void* block2 = NULL;
    void* memory = NULL;

    suggested_size = FSASuggestSize(block_size, n_blocks);
    TEST("Test suggested size",suggested_size , 208);

    memory = (void*)malloc(suggested_size);

    fsa = FSAInit(memory, block_size, suggested_size);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks);

    block1 = FSAAlloc(fsa);
    block2 = FSAAlloc(fsa);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks-2);

    FSAFree(fsa, block1);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks-1);

    free(memory);
}

/*test fsa when given unaligned block_size*/

void TestFSASimple2() 
{
    size_t block_size = 31;
    size_t n_blocks = 5;
    fsa_t* fsa = NULL;
    size_t suggested_size = 0;
    void* block1 = NULL;
    void* block2 = NULL;
    void* memory = NULL;

    suggested_size = FSASuggestSize(block_size, n_blocks);
    TEST("Test suggested size",suggested_size , 208);

    memory = (void*)malloc(suggested_size);

    fsa = FSAInit(memory, block_size, suggested_size);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks);

    block1 = FSAAlloc(fsa);
    block2 = FSAAlloc(fsa);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks-2);

    FSAFree(fsa, block1);

    TEST("Count free blocks", FSACountFree(fsa), n_blocks-1);

    free(memory);

}

/*test fsa when user didn't use suggested memory*/

void TestFSAAdvanced() 
{
    size_t block_size = 31;
    size_t n_blocks = 5;
    fsa_t* fsa = NULL;
    size_t suggested_size = 0;
    void* block1 = NULL;
    void* block2 = NULL;
    void* memory = NULL;
    size_t memory_size = 120;

    suggested_size = FSASuggestSize(block_size, n_blocks);

    TEST("Test suggested size",suggested_size != memory_size, 1);

    memory = (void*)malloc(memory_size);

    fsa = FSAInit(memory, block_size, memory_size);

    TEST("Count free blocks", FSACountFree(fsa), 2);

    block1 = FSAAlloc(fsa);
    block2 = FSAAlloc(fsa);

    TEST("Count free blocks", FSACountFree(fsa), 0);

    TEST("Cannot give more memory", FSAAlloc(fsa), NULL);

    FSAFree(fsa, block1);

    TEST("Count free blocks", FSACountFree(fsa), 1);

    free(memory);

}

int main()
{
	TestFSASimple1();
    TestFSASimple2();
    TestFSAAdvanced();
	PASS;
	return 0;
}