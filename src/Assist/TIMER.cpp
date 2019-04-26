#include "TIMER.h"

void TIMER::Reset()
{
	// ��ʼʱ��
	startTime = chrono::high_resolution_clock::now();
}

chrono::milliseconds TIMER::GetTime()
{
	if (isPaused)
		return duration_cast<milliseconds>(pauseTime - startTime);
	else
		return duration_cast<milliseconds>(high_resolution_clock::now()-startTime);
}

void TIMER::Pause()
{
	//Only pause if currently unpaused
	if (isPaused)
		return;
		
	isPaused = true;
	pauseTime = high_resolution_clock::now();  // ��¼��ͣ��ʱ��
}

void TIMER::Unpause()
{
	//Only unpause if currently paused
	if (!isPaused)
		return;
	
	isPaused = false;
	
	//Update start time to reflect pause
	startTime += (high_resolution_clock::now() - pauseTime);
}
