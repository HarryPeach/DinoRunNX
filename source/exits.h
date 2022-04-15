#include <switch.h>

// Exits the program, while also clearing up initialised resources and displaying any errors outputted during the run
int exit_program(int code, unsigned long long sleep_timer);

// Exits the program and pauses to view any displayed errors
int exit_error();

// Exits the program immediately
int exit_graceful();