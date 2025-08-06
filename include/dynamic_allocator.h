#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/* 
*   @desc:          Initializes a memory pool for VSA. The memory pool's blocks 
*                   can be allocated and freed individually.
*   @params:        @memory: Pointer to the start of the preallocated memory block.
*				    @memory_size : Total memory size in bytes.
*   @return value:  Pointer to the VSA structure, and returns NULL if @memory_size
*                   is not big enough to init VSA structure.
*   @error: 		Undefined behavior if @memory is invalid and
*                   allocated less memory than @memory_size.
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
vsa_t* VSAInit(void* memory, size_t memory_size);

/* 
*   @desc:          Returns the pointer to the new allocated block.
*   @params: 	    @vsa: pointer to pre-initialized @vsa.
                    @alloc_size: size to allocate.
*   @return value:  Returns NULL if no free space available or if @alloc_size is 0
*   @error: 		Undefined behavior if @vsa is invalid.
*   @time complex: 	O(n)
*   @space complex: O(1)
*/
void* VSAAlloc(vsa_t* vsa, size_t alloc_size);

/* 
*   @desc:          Frees a pre-allocated memory block. if @block is NULL
*                   no operation will be performed.
*   @params: 	    @block: Pointer to pre-allocated block
*   @return value:  None
*   @error: 		Undefined behavior if @block is incorrect
*   @time complex: 	O(1)
*   @space complex: O(1)
*/
void VSAFree(void* block);

/* 
*   @desc:          Returns the size of the largest available memory block.
*   @params:        @vsa: Pointer to the initialized @vsa.
*   @return value:  Size of the largest free block in bytes.
*   @error:         Returns 0 if no free blocks are available.
*   @time complex:  O(n)
*   @space complex: O(1)
*/
size_t VSALargestChunkAvailable(vsa_t* vsa);

#endif      /* __VSA_H__ */                            