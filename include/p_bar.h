#ifndef PBAR_H
#define PBAR_H

typedef struct {
	float progress;
	int filled;
	int percentages;
} p_bar;

void update_bar_values(p_bar *bar, int total_seconds, int initial_seconds);

#endif