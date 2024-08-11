#include <stm32f4_discovery.h>
#include <os.h>

evq_t evq = EVQ_INIT(1);

void consumer()
{
	unsigned x;

	for (;;)
	{
		evq_wait(&evq, &x);
		LEDs = x & 0x0FUL;
	}
}

void producer()
{
	unsigned x = 1;

	for (;;)
	{
		tsk_delay(SEC);
		evq_give(&evq, x);
		x = (x << 1) | (x >> 3);
	}
}

tsk_t cons = TSK_INIT(0, consumer, 256);
tsk_t prod = TSK_INIT(0, producer, 256);

int main()
{
	LED_Init();

	tsk_start(&cons);
	tsk_start(&prod);
	tsk_stop();
}
