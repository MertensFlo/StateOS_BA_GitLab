#include <stm32f4_discovery.h>
#include <os.h>

using namespace device;
using namespace stateos;
using namespace std::chrono_literals;

void proc( unsigned &led, Clock::time_point timePoint )
{
	thisTask::sleepUntil(timePoint);
	for (;;)
	{
		thisTask::sleepNext(500ms);
		led++;
	}
}

int main()
{
	auto led = Led();
	auto grn = GreenLed();
	auto now = Clock::now();

	auto t1 = Task::Start(0, [&]{ proc(led[0], now +   0ms); });
	auto t2 = Task::Start(0, [&]{ proc(led[1], now + 125ms); });
	auto t3 = Task::Start(0, [&]{ proc(led[2], now + 250ms); });
	auto t4 = Task::Start(0, [&]{ proc(led[3], now + 375ms); });
	auto t5 = Task::Start(0, [&]{ proc(grn,    now + 500ms); });

	thisTask::stop();
}
