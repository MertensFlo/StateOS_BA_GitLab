#include <stm32f4_discovery.h>
#include <os.h>
#include <stdlib.h>

// Sleeping barber problem

#define BARBERS   2 // num of barbers
#define CUSTOMERS 4 // num of chairs in the waiting room
#define DELAY   256 // time constant

OS_MTX(doors, mtxDefault);
OS_SEM(barbers,   0);
OS_SEM(customers, 0);
OS_SEM(end_of_haircut, 0);

int free_seats = CUSTOMERS; // num of free seats in the waiting room

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
		mtx_lock(doors);
		free_seats++;
		sem_give(barbers);
		mtx_unlock(doors);
		cut_hair();
	}
}

void customer()
{
	mtx_lock(doors);
	if (free_seats > 0)
	{
		free_seats--;
		sem_give(customers);
		mtx_unlock(doors);
		sem_wait(barbers);
		get_haircut();
	}
	else
	{
		mtx_unlock(doors);
	}

	tsk_delete(SELF);
}		

int main()
{
	cnt_t dly;
	int i;

	srand(0);
	LED_Init();

	for (i = 0; i < BARBERS; i++)
		tsk_new(1, barber);

	for (;;)
	{
		tsk_new(1, customer);

		dly = (unsigned)rand() % DELAY;
		tsk_delay(dly * MSEC);
	}
}
