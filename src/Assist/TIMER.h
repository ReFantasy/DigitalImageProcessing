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
	chrono::milliseconds GetTime();  // ��λ����

	void Pause();
	void Unpause();

protected:
	chrono::time_point<high_resolution_clock> startTime;  // ��ʼʱ���
	bool isPaused; // ��ͣ����
	chrono::time_point<high_resolution_clock> pauseTime;  // ��ͣʱ���
};


#endif	//TIMER_H