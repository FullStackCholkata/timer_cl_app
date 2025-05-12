#ifndef GRAPHICS_H
#define GRAPHICS_H

typedef struct {
	int b_height;
	int b_width;
	int t_rows;
	int t_cols;
} Graphics;

void clear_sceen();
void calculate_terminal_dimensions(Graphics* g);
void calculate_center_position(Graphics* g, int* start_row, int* start_col);
void draw_box(Graphics g, int start_row, int start_col);

#endif 