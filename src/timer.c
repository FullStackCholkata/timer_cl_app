#include <stdio.h>
#include <stdlib.h>
#include "timer.h" 

int parse_time(int argc, char *argv[], Timer* timer) {
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <time in HH:MM:SS format>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *time_str =  argv[1];
    int token;

    // Parse hours
    token = strtok(time_str, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        exit(EXIT_FAILURE);
    }
    timer->hours = atoi(token);

    // Parse minutes
    token = strtok(NULL, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        exit(EXIT_FAILURE);
    }
    timer->minutes = atoi(token);

    // Parse seconds
    token = strtok(NULL, ":");
    if (token == NULL) {
        fprintf(stderr, "Not a valid format!\n");
        exit(EXIT_FAILURE);
    }
    timer->seconds = atoi(token);

    // Check if provided values are valid
    if (timer->hours < 0 || timer->hours > 24) {
        fprintf(stderr, "Hours should be between 0 and 24!\n");
        exit(EXIT_FAILURE);
    }
    if (timer->minutes < 0 || timer->minutes > 60) {
        fprintf(stderr, "Minutes should be between 0 and 60!\n");
        exit(EXIT_FAILURE);
    }
    if (timer->seconds < 0 || timer->seconds > 60) {
        fprintf(stderr, "Seconds should be between 0 and 60!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void start_timer(Timer* timer) {
    // Implementation code here
}