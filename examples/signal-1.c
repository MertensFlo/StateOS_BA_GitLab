#include <stm32f4_discovery.h>
#include <os.h>

sig_t sig = SIG_INIT();

void consumer()
{
	sig_wait(&sig, SIGSET(1), NULL);
	LED_Tick();
}

void producer()
{
	tsk_delay(SEC);
	sig_give(&sig, 1);
}

tsk_t cons = TSK_INIT(0, consumer);
tsk_t prod = TSK_INIT(0, producer);

int main()
{
	LED_Init();

	tsk_start(&cons);
	tsk_start(&prod);
	tsk_stop();
}
