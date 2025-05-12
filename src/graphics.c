#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>    // For Windows-specific console functions
#else
#include <sys/ioctl.h>  // For getting terminal size
#include <unistd.h>     // For STDOUT_FILENO and other POSIX functions
#endif

#include "../include/graphics.h"

void clear_screen() {
	// Clears the entire screen
	printf("\033[2J");
	// Moves the cursor to home position (0,0)
	printf("\033[H");
}

void calculate_terminal_dimensions(Graphics* g) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            g->t_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            g->t_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        } else {
            g->t_rows = 25;
            g->t_cols = 80;
        }
    #else
        struct winsize window;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
        g->t_rows = window.ws_row;
        g->t_cols = window.ws_col;
    #endif
}

void calculate_center_position(Graphics* g, int* start_row, int* start_col) {
	*start_col =  (g->t_cols - g->b_width) / 2;
	*start_row = (g->t_rows - g->b_height) / 2;
}

void draw_box(Graphics g, int start_row, int start_col) {
	printf("\033[%d;%dH", start_row, start_col);
	printf("┌");
	for (int i = 1; i < g.b_width; i++) {
		printf("\033[%d;%dH", start_row, start_col + 1);
		printf("─");
	}
	printf("\033[%d;%dH", start_row, start_col + g.b_width);
	printf("┐");

	for (int i = 1; i < g.b_height; i++) {
		// TODO
	}
}

// Maybe the box should be a fixed size. 
// It doesn't really make sense to change the size when the timer always stays the same HH:MM:SS