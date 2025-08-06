#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h>     /* size_t */

typedef struct fsa fsa_t;

/* 
*   @desc:          Returns the suggested size of memory according to 
*                   @block_size and @n_blocks.
*   @params: 	    @block_size: the number of bytes in block
*				    @n_blocks: the number of blocks
*   @return value:  The suggested total memory size.
*   @error: 		None.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
size_t FSASuggestSize(size_t block_size, size_t n_blocks);

/* 
*   @desc:          Creates and initilizes the FSA structure.
*   @params: 	    @memory: Pointer to the start of the preallocated memory block.
*                   @block_size: Block size in bytes.
*				    @memory_size : Total memory size in bytes.
*   @return value:  Pointer to the FSA structure.
*   @error: 		Returns NULL if @block_size exceeds @memory_size
*                   undefined behavior if @memory is invalid and
*                   allocated less memory than @memory_size.
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
fsa_t* FSAInit(void* memory, size_t block_size, size_t memory_size);

/* 
*   @desc:          Returns the pointer to the first empty block.
*   @params: 	    @fsa: Pre-initialized FSA structure.
*   @return value:  Returns a pointer to an allocated block
*   @error: 		Returns NULL if no free block available
*                   undefined behavior if @fsa is invalid
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void* FSAAlloc(fsa_t* fsa);

/* 
*   @desc:          Frees @p_block.
*   @params: 	    @fsa: Pre-initialized FSA structure.
*				    @p_block: Pointer to pre-allocated blocks.
*   @return value:  None.
*   @error: 		undefined behavior if @fsa is invalid.
*   @time complex: 	O(1) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
void FSAFree(fsa_t* fsa, void* p_block);

/* 
*   @desc:          Returns the amount of free blocks currently contained 
*                   within @fsa.
*   @params: 	    @fsa: Pre-initialized FSA structure.
*   @return value:  The number of free blocks.
*   @error: 		undefined behavior if @fsa is invalid.
*   @time complex: 	O(n) for both AC/WC
*   @space complex: O(1) for both AC/WC
*/
size_t FSACountFree(const fsa_t* fsa);

#endif  /* fsa.h */


