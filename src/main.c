#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../include/timer.h"

int main(int argc, char *argv[]) {
    Timer this_timer;

    parse_time(argc, argv, &this_timer);
    printf("Hours: %d\n", this_timer.hours);
    printf("Minutes: %d\n", this_timer.minutes);
    printf("Seconds: %d\n", this_timer.seconds);
    printf("\n");  // Add an extra newline at the end

    return 0;
}