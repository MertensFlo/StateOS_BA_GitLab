#include "test.h"

static void proc()
{
	         tsk_stop();
}

static void test()
{
	int result;

	tsk_t tsk9 = TSK_INIT(9, proc);
	tsk_t tsk8 = TSK_INIT(8, proc);
	tsk_t tsk7 = TSK_INIT(7, proc, 256);
	tsk_t tsk6 = TSK_INIT(6, proc, 512);

	         tsk_start(&tsk9);                    ASSERT_dead(&tsk9);
	result = tsk_join(&tsk9);                     ASSERT_success(result);
	         tsk_start(&tsk8);                    ASSERT_dead(&tsk8);
	result = tsk_join(&tsk8);                     ASSERT_success(result);
	         tsk_start(&tsk7);                    ASSERT_dead(&tsk7);
	result = tsk_join(&tsk7);                     ASSERT_success(result);
	         tsk_start(&tsk6);                    ASSERT_dead(&tsk6);
	result = tsk_join(&tsk6);                     ASSERT_success(result);
}

void test_task_create_0()
{
	TEST_Notify();
	TEST_Call();
}
