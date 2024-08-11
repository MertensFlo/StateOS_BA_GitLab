#include <stm32f4_discovery.h>
#include <os.h>
#include <stdlib.h>

// Sleeping barber problem

#define BARBERS   2 // num of barbers
#define CUSTOMERS 4 // num of chairs in the waiting room
#define DELAY   256 // time constant

OS_SEM(barbers,   0, BARBERS);
OS_SEM(customers, 0, CUSTOMERS);
OS_SEM(end_of_haircut, 0);

void cut_hair()
{
	static cnt_t dly = 0;

	dly = (dly + 4) % DELAY;
	tsk_delay(dly * MSEC);

	sem_give(end_of_haircut);
}

void get_haircut()
{
	LED_Tick();

	sem_wait(end_of_haircut);
}

void barber()
{
	for (;;)
	{
		sem_wait(customers);
		sem_give(barbers);
		cut_hair();
	}
}

void customer()
{
	if (sem_give(customers) == E_SUCCESS)
	{
		sem_wait(barbers);
		get_haircut();
	}

	tsk_stop();
}		

int main()
{
	cnt_t dly;
	int i;

	srand(0);
	LED_Init();

	for (i = 0; i < BARBERS; i++)
		tsk_detached(1, barber);

	for (;;)
	{
		tsk_detached(1, customer);

		dly = (unsigned)rand() % DELAY;
		tsk_delay(dly * MSEC);
	}
}
