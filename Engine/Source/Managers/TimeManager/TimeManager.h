// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Joint authors Vitatiy Paravishnik, Andrey Sidorov and other.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace TimeManager
//
//		This namespace contains additional handlers for the time
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SYS_H_
#define _SYS_H_

#include <time.h>

namespace TimeManager
{
	extern unsigned long g_last_steptime;

	unsigned long get_time_ms(); // ms
	void update_steptime();
	inline unsigned long get_steptime_ms()
	{
		return g_last_steptime;   // ms
	}
	inline float get_steptime_s()
	{
		return ( ( float ) get_steptime_ms() / 1000.0 );   // s
	}

	void sleep ( unsigned long sleep_time ); // ms

	clock_t clock();
}

#endif // _SYS_H_
