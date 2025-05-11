#ifndef TIMER_H
#define TIMER_H

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Timer;

int parse_time(int argc, char *argv[], Timer* timer);
void start_timer(Timer* timer); 

#endif
