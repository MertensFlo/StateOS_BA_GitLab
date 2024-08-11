#include <stm32f4_discovery.h>
#include <os.h>

OS_FLG(flg, 1);

void consumer()
{
	flg_wait(flg, 1, flgProtect+flgIgnore);
	LED_Tick();
}

void producer()
{
	tsk_delay(SEC);
	flg_give(flg, 1);
}

OS_TSK(cons, 0, consumer);
OS_TSK(prod, 0, producer);

int main()
{
	LED_Init();

	tsk_start(cons);
	tsk_start(prod);
	tsk_stop();
}
