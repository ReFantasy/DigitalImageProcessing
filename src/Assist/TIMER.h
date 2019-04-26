#ifndef TIMER_H
#define TIMER_H
#include <chrono>
using namespace std;
using namespace chrono;

class TIMER
{
public:
	TIMER() : isPaused(false)
	{
		Reset();
	}
	~TIMER() {}

	void Reset();
	chrono::milliseconds GetTime();  // 单位毫秒

	void Pause();
	void Unpause();

protected:
	chrono::time_point<high_resolution_clock> startTime;  // 开始时间点
	bool isPaused; // 暂停开关
	chrono::time_point<high_resolution_clock> pauseTime;  // 暂停时间点
};


#endif	//TIMER_H