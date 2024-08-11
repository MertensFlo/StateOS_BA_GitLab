#include <stm32f4_discovery.h>
#include <os.h>

sig_id sig = SIG_CREATE(0);

void consumer()
{
	unsigned x;

	sig_wait(sig, sigAny, &x);
	LEDs = x & 0x0FUL;
}

void producer()
{
	unsigned x = 1;

	for (;;)
	{
		tsk_delay(SEC);
		sig_give(sig, x);
		x = (x << 1) | (x >> 3);
	}
}

int main()
{
	LED_Init();

	tsk_start((tsk_id)TSK_CREATE(0, consumer));
	tsk_start((tsk_id)TSK_CREATE(0, producer));
	tsk_sleep();
}
