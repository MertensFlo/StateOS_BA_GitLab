#include "test.h"

void test_fast_mutex()
{
	UNIT_Notify();
	TEST_Add(test_fast_mutex_1);
#ifndef __CSMC__
	TEST_Add(test_fast_mutex_2);
	TEST_Add(test_fast_mutex_3);
#endif
}
