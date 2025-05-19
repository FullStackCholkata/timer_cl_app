#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // Windows specific
#else
#include <unistd.h> // POSIX systems (Linux, macOS)
#endif

#include "../include/timer.h"
#include "../include/graphics.h"
#include "../include/p_bar.h"

int parse_time(int argc, char *argv[], Timer *timer)
{

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <time in HH:MM:SS format>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	char *time_str = strdup(argv[1]);
	char *token;

	// Parse hours
	token = strtok(time_str, ":");
	if (token == NULL)
	{
		fprintf(stderr, "Not a valid format!\n");
		return 1;
	}
	timer->hours = atoi(token);

	// Parse minutes
	token = strtok(NULL, ":");
	if (token == NULL)
	{
		fprintf(stderr, "Not a valid format!\n");
		return 1;
	}
	timer->minutes = atoi(token);

	// Parse seconds
	token = strtok(NULL, ":");
	if (token == NULL)
	{
		fprintf(stderr, "Not a valid format!\n");
		return 1;
	}
	timer->seconds = atoi(token);

	// Check if provided values are valid
	if (timer->hours < 0 || timer->hours > 24)
	{
		fprintf(stderr, "Hours should be between 0 and 24!\n");
		return 1;
	}
	if (timer->minutes < 0 || timer->minutes > 59)
	{
		fprintf(stderr, "Minutes should be between 0 and 59!\n");
		return 1;
	}
	if (timer->seconds < 0 || timer->seconds > 59)
	{
		fprintf(stderr, "Seconds should be between 0 and 59!\n");
		return 1;
	}

	return 0;
}

void start_timer(Timer *timer)
{
	// Create a terminal details struct and fill it up with the size of teh current terminal
	Terminal ter;
	calculate_terminal_dimensions(&ter);

	int start_col = 0, start_row = 0;
	calculate_center_position(ter, &start_row, &start_col);

	int total_seconds = timer->hours * 3600 + timer->minutes * 60 + timer->seconds;
	int initial_total_seconds = total_seconds;
	p_bar bar;

	hide_cursor();

	while (total_seconds > 0)
	{
		clear_screen();

		int remaining_h = total_seconds / 3600;
		int remaining_m = (total_seconds % 3600) / 60;
		int remaining_s = total_seconds % 60;

		update_bar_values(&bar, total_seconds, initial_total_seconds);

		draw_box(start_row, start_col);

		// Position cursor inside the box
		printf("\033[%d;%dH", start_row + 2, start_col + 3);
		printf("%02dh %02dm %02ds", remaining_h, remaining_m, remaining_s);
		
		draw_p_bar(bar, start_row, start_col);
		
		#ifdef _WIN32
				Sleep(1000);
		#else
				sleep(1);
		#endif

		total_seconds--;
	}

	draw_end_box(ter, start_row, start_col);
}