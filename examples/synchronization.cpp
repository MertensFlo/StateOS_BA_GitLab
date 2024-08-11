#include <stm32f4_discovery.h>
#include <os.h>

using namespace device;
using namespace stateos;

auto led = Led();
auto one = OnceFlag();

void tickLoop(Semaphore &own, Semaphore &another)
{
	for (;;)
	{
		one.call([]{ led = 0; });
		own.wait();
		thisTask::delay(SEC);
		led.tick();
		another.post();
	}
}

auto cons_sem = Semaphore(0);
auto prod_sem = Semaphore(1);

auto cons = Task::Start(0, []{ tickLoop(cons_sem, prod_sem); });
auto prod = Task::Start(0, []{ tickLoop(prod_sem, cons_sem); });

int main()
{
	thisTask::sleep();
}
