#include "test.h"

void test_barrier()
{
	UNIT_Notify();
	TEST_Add(test_barrier_1);
#ifndef __CSMC__
	TEST_Add(test_barrier_2);
	TEST_Add(test_barrier_3);
#endif
}
