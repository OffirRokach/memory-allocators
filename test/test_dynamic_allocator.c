#include <stdlib.h> /*malloc , calloc*/

#include "testing_macros.h"
#include "vsa.h"

void TestVSA(void)
{
	void* memory = malloc(1000);
	void* allocations[8] = { NULL };
	size_t i = 0;

	vsa_t* vsa = VSAInit(memory, 16);
	TEST("Should fail since not enough space", vsa, NULL);

	vsa = VSAInit(memory, 32);
#ifndef NDEBUG
	TEST("Should fail since not enough space", vsa, NULL);
#else
	TEST("Should succeed since there is enough space", vsa != NULL, 1);
#endif
	vsa = VSAInit(memory, 1000);
	TEST("Largest chunk available is less than the memory size", VSALargestChunkAvailable(vsa) < 1000, 1);

	allocations[0] = VSAAlloc(vsa, 5);
	allocations[1] = VSAAlloc(vsa, 3);
	allocations[2] = VSAAlloc(vsa, 7);
	allocations[3] = VSAAlloc(vsa, 4);
	allocations[4] = VSAAlloc(vsa, 19);
	allocations[5] = VSAAlloc(vsa, 4);
	allocations[6] = VSAAlloc(vsa, 22);
	allocations[7] = VSAAlloc(vsa, VSALargestChunkAvailable(vsa));

	for (i = 0; i < 8; ++i)
	{
		TEST("Alloc success", allocations[i] != NULL, 1);
	}

	TEST("No more space", VSALargestChunkAvailable(vsa), 0);

	VSAFree(allocations[2]);
	VSAFree(allocations[3]);
	VSAFree(allocations[4]);

	TEST("Defrag on largest chunk", VSALargestChunkAvailable(vsa) > 7 + 4 + 19 + 8 + 8, 1);

	allocations[2] = VSAAlloc(vsa, VSALargestChunkAvailable(vsa) - 12);

	TEST("No more space even though there is some space", VSALargestChunkAvailable(vsa), 0);

	VSAFree(allocations[6]);
	VSAFree(allocations[0]);

	allocations[0] = VSAAlloc(vsa, 30);
	TEST("Failed to allocate", allocations[0], NULL);

	VSAFree(allocations[5]);
	allocations[0] = VSAAlloc(vsa, 32);

	TEST("Success to allocate", allocations[0] != NULL, 1);

	free(memory);
}


int main(void)
{
	TestVSA();
	PASS;
	return 0;
}
