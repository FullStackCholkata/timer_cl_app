#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>  // Windows specific
#else
#include <unistd.h>   // POSIX systems (Linux, macOS)
#endif

#include "timer.h" 

int parse_time(int argc, char *argv[], Timer* timer) {
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <time in HH:MM:SS format>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *time_str = strdup(argv[1]);
    char* token;

    // Parse hours
    token = strtok(time_str, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        return 1;
    }
    timer->hours = atoi(token);

    // Parse minutes
    token = strtok(NULL, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        return 1;
    }
    timer->minutes = atoi(token);

    // Parse seconds
    token = strtok(NULL, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        return 1;
    }
    timer->seconds = atoi(token);

    // Check if provided values are valid
    if (timer->hours < 0 || timer->hours > 24) {
        fprintf(stderr, "Hours should be between 0 and 24!\n");
        return 1;
    }
    if (timer->minutes < 0 || timer->minutes > 59) {
        fprintf(stderr, "Minutes should be between 0 and 59!\n");
        return 1;
    }
    if (timer->seconds < 0 || timer->seconds > 59) {
        fprintf(stderr, "Seconds should be between 0 and 59!\n");
        return 1;
    }

    return 0;
}

void start_timer(Timer* timer) {

    int total_seconds = timer->hours * 3600 + timer->minutes * 60 + timer->seconds;

	printf("Started timer for %02dh %02dm %02ds\n", timer->hours, timer->minutes, timer->seconds);

	while (total_seconds > 0) {

		int remaining_h = total_seconds / 3600;
		int remaining_m = (total_seconds % 3600) / 60;
		int remaining_s = total_seconds % 60;

		fprintf(stdout ,"\r%02dh %02dm %02ds", remaining_h, remaining_m, remaining_s);
		fflush(stdout);

		#ifdef _WIN32
		Sleep(1000);
		#else
		sleep(1);
		#endif

		total_seconds--;

	}

	printf("\nTimer is done!\n");
	
}