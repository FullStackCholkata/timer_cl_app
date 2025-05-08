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
    fprintf(stdout, "Hours: %d\n", this_timer.hours);
    fprintf(stdout, "Minutes: %d\n", this_timer.minutes);
    fprintf(stdout, "Seconds: %d\n", this_timer.seconds);

    return 0;
}