#include "test.h"

static_MTX(mtx3, mtxRobust);

static void proc5()
{
	int result;

	result = mtx_wait(mtx3);                      ASSERT_owndead(result);
	result = mtx_give(mtx3);                      ASSERT_success(result);
	         tsk_stop();
}

static void proc4()
{
	int result;

	result = mtx_wait(mtx3);                      ASSERT_success(result);
	                                              ASSERT_dead(tsk5);
	         tsk_startFrom(tsk5, proc5);          ASSERT_ready(tsk5);
	result = mtx_wait(mtx1);                      ASSERT(!"test program cannot be caught here");
}

static void proc3()
{
	int result;

	result = mtx_take(mtx2);                      ASSERT_timeout(result);
	result = mtx_wait(mtx3);                      ASSERT_success(result);
	result = mtx_take(mtx3);                      ASSERT_timeout(result);
	                                              ASSERT_dead(tsk4);
	         tsk_startFrom(tsk4, proc4);          ASSERT_ready(tsk4);
	result = mtx_give(mtx3);                      ASSERT_success(result);
	result = mtx_give(mtx3);                      ASSERT_failure(result);
	result = tsk_kill(tsk4);                      ASSERT_success(result);
	result = tsk_join(tsk5);                      ASSERT_success(result);
	         tsk_stop();
}

static void proc2()
{
	int result;

	result = mtx_take(mtx1);                      ASSERT_timeout(result);
	result = mtx_wait(mtx2);                      ASSERT_success(result);
	result = mtx_take(mtx2);                      ASSERT_success(result);
	                                              ASSERT_dead(tsk3);
	         tsk_startFrom(tsk3, proc3);          ASSERT_dead(tsk3);
	result = tsk_join(tsk3);                      ASSERT_success(result);
	result = mtx_give(mtx2);                      ASSERT_success(result);
	result = mtx_give(mtx2);                      ASSERT_success(result);
	         tsk_stop();
}

static void proc1()
{
	int result;

	result = mtx_take(&mtx0);                     ASSERT_timeout(result);
	result = mtx_wait(mtx1);                      ASSERT_success(result);
	result = mtx_take(mtx1);                      ASSERT_failure(result);
	                                              ASSERT_dead(tsk2);
	         tsk_startFrom(tsk2, proc2);          ASSERT_dead(tsk2);
	result = tsk_join(tsk2);                      ASSERT_success(result);
	result = mtx_give(mtx1);                      ASSERT_success(result);
	result = mtx_give(mtx1);                      ASSERT_failure(result);
	         tsk_stop();
}

static void proc0()
{
	int result;

	result = mtx_wait(&mtx0);                     ASSERT_success(result);
	result = mtx_take(&mtx0);                     ASSERT_timeout(result);
	                                              ASSERT_dead(tsk1);
	         tsk_startFrom(tsk1, proc1);          ASSERT_dead(tsk1);
	result = tsk_join(tsk1);                      ASSERT_success(result);
	result = mtx_give(&mtx0);                     ASSERT_success(result);
	result = mtx_give(&mtx0);                     ASSERT_success(result);
	         tsk_stop();
}

static void test()
{
	int result;
	                                              ASSERT_dead(&tsk0);
	         tsk_startFrom(&tsk0, proc0);
	result = tsk_join(&tsk0);                     ASSERT_success(result);
}

extern "C"
void test_mutex_4()
{
	TEST_Notify();
	mtx_init(&mtx0, mtxNormal, 0);
	mtx_init(mtx1, mtxErrorCheck, 0);
	mtx_init(mtx2, mtxRecursive, 0);
	TEST_Call();
}
