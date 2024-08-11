#include <stm32f4_discovery.h>
#include <os.h>

using namespace device;
using namespace stateos;

void consumer(Semaphore &sem, Led &led)
{
	for (;;)
	{
		sem.wait();
		led.tick();
	}
}

void producer(Semaphore &sem)
{
	for (;;)
	{
		thisTask::sleepFor(SEC);
		sem.give();
	}
}

int main()
{
	Led led;
	Semaphore sem;
	auto cons = Task::Start(0, [&]{ consumer(sem, led); });
	auto prod = Task::Start(0, [&]{ producer(sem); });
	thisTask::sleep();
}
