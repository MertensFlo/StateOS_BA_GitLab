#include <stm32f4_discovery.h>
#include <os.h>

using namespace device;
using namespace stateos;

auto led = Led();
auto evt = Event();

void consumer()
{
	unsigned x;

	evt.wait(&x);
	led = x;
}

void producer()
{
	unsigned x = 1;

	for (;;)
	{
		thisTask::delay(SEC);
		evt.give(x);
		x = (x << 1) | (x >> 3);
	}
}

auto cons = Task(0, consumer);
auto prod = Task(0, producer);

int main()
{
	cons.start();
	prod.start();

	thisTask::stop();
}
