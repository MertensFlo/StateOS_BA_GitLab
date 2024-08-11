#include "test.h"

static unsigned sent = 0;
static unsigned received = 0;

static void action( unsigned signo )
{
	         received = signo;
}

static void proc2()
{
	         sent = (unsigned)rand() % SIG_LIMIT;
	         tsk_signal(tsk1, sent);
	         tsk_stop();
}

static void proc1()
{
	         tsk_action(SELF, action);
	         tsk_suspend(SELF);                   ASSERT(sent == received);
	         tsk_action(SELF, nullptr);
	         tsk_stop();
}

static void test()
{
	int result;
	                                              ASSERT_dead(tsk1);
	         tsk_startFrom(tsk1, proc1);          ASSERT_ready(tsk1);
	                                              ASSERT_dead(tsk2);
	         tsk_startFrom(tsk2, proc2);          ASSERT_dead(tsk2);
	result = tsk_join(tsk2);                      ASSERT_success(result);
	result = tsk_resume(tsk1);                    ASSERT_success(result);
	result = tsk_join(tsk1);                      ASSERT_success(result);
}

extern "C"
void test_task_signal_2()
{
	TEST_Notify();
	TEST_Call();
}
