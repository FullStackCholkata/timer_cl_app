#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "p_bar.h"

typedef struct {
	int t_rows;
	int t_cols;
} Terminal;

void clear_screen();
void calculate_terminal_dimensions(Terminal* details);
void calculate_center_position(Terminal details, int* start_row, int* start_col);
void draw_box(int start_row, int start_col);
void draw_p_bar(p_bar bar, int start_row, int start_col);
void draw_end_box(Terminal ter, int start_row, int start_col);
void hide_cursor();
void show_cursor();

#endif 