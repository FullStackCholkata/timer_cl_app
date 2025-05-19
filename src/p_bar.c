#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // For Windows-specific console functions
#else
#include <sys/ioctl.h> // For getting terminal size
#include <unistd.h>	   // For STDOUT_FILENO and other POSIX functions
#endif

#include "../include/graphics.h"
#include "../include/p_bar.h"

void update_bar_values(p_bar *bar, int total_seconds, int initial_seconds) {
	bar->progress = 1.0f - ((float) total_seconds / initial_seconds);
	bar->filled = (int) (bar->progress * 13);
	bar->percentages = bar->progress * 100;
}