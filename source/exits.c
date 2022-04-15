#include "exits.h"

int exit_program(int code, unsigned long long sleep_timer)
{
	consoleUpdate(NULL);
	svcSleepThread(sleep_timer);
	consoleExit(NULL);
	return code;
}

int exit_error()
{
	return exit_program(1, 5000000000ull);
}

int exit_graceful()
{
	return exit_program(0, 0ull);
}