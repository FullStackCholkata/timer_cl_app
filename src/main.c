#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "../include/timer.h"

int main(int argc, char *argv[]) {

    Timer this_timer;

    if (parse_time(argc, argv, &this_timer) != 0) {
		return EXIT_FAILURE;
	}

	start_timer(&this_timer);

    return 0;
}