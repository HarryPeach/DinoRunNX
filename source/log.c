#include <stdio.h>
#include <stdarg.h>

#include "log.h"

void log_dbg(const char *text, ...)
{
	va_list args;
	va_start(args, text);
	vprintf(text, args);
	va_end(args);
	consoleUpdate(NULL);
}

void log_err(const char *text, ...)
{
	va_list args;
	va_start(args, text);
	vprintf(text, args);
	printf(CONSOLE_RESET);
	va_end(args);
	consoleUpdate(NULL);
}