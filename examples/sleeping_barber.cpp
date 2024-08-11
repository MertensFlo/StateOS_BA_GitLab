#include <stm32f4_discovery.h>
#include <os.h>
#include <stdlib.h>

// Sleeping barber problem

#define BARBERS   2 // num of barbers
#define CUSTOMERS 4 // num of chairs in the waiting room
#define DELAY   256 // time constant

using namespace device;
using namespace stateos;

auto led            = Led();
auto barbers        = Semaphore(0, BARBERS);
auto customers      = Semaphore(0, CUSTOMERS);
auto end_of_haircut = Semaphore(0);

void cut_hair()
{
	static cnt_t dly = 0;

	dly = (dly + 4) % DELAY;
	thisTask::delay(dly * MSEC);

	end_of_haircut.give();
}

void get_haircut()
{
	led.tick();

	end_of_haircut.wait();
}

void barber()
{
	for (;;)
	{
		customers.wait();
		barbers.give();
		cut_hair();
	}
}

void customer()
{
	if (customers.give() == E_SUCCESS)
	{
		barbers.wait();
		get_haircut();
	}

	thisTask::destroy();
}		

int main()
{
	srand(0);

	for (int i = 0; i < BARBERS; i++)
		Task::Create(1, barber);

	for (;;)
	{
		Task::Create(1, customer);

		cnt_t dly = (unsigned)rand() % DELAY;
		thisTask::delay(dly * MSEC);
	}
}
