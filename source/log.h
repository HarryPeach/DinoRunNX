#include <switch.h>

// Writes a log to the console, and updates the console
void log_dbg(const char *text, ...);

// Writes an error to the console and then updates the console
void log_err(const char *text, ...);