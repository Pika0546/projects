#include "GameHeader.h"

tm getNow()
{
	system_clock::time_point getClock = system_clock::now();
	time_t setClock = system_clock::to_time_t(getClock);
	tm* resultClock = localtime(&setClock);
	tm result = *resultClock;
	return correctNow(result);
}

tm correctNow(tm Now)
{
	Now.tm_mon++;
	Now.tm_year += 1900;
	return Now;
}

#pragma region Wait 
bool wait(seconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<seconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

bool wait(milliseconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<milliseconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

bool waitPause(milliseconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<milliseconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

bool waitAddtime(milliseconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<milliseconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

bool waitClock(milliseconds time)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();

	static bool reset = false;
	if (reset) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<milliseconds>(b - a) >= time) { reset = true; return true; }
	else { reset = false; return false; }
}

#pragma endregion

bool countdown(seconds& time, bool reset)
{
	static steady_clock::time_point a = steady_clock::now();
	static steady_clock::time_point b = steady_clock::now();
	static bool start = true;

	if (reset)
	{
		a = steady_clock::now();
		return false;
	}

	if (time <= 0s)
	{
		time = 0s;
		start = true;
		return true;
	}
	if (start) a = steady_clock::now();
	b = steady_clock::now();
	if (duration_cast<seconds>(b - a) >= 1s)
	{
		time -= duration_cast<seconds>(b - a);
		a = steady_clock::now();
	}
	start = false;
	return false;
}

bool stop(milliseconds time)
{
	steady_clock::time_point a = steady_clock::now();
	steady_clock::time_point b;
	do
	{
		b = steady_clock::now();
	} while (duration_cast<milliseconds>(b - a) <= time);
	return true;
}