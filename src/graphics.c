#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // For Windows-specific console functions
#else
#include <sys/ioctl.h> // For getting terminal size
#include <unistd.h>	   // For STDOUT_FILENO and other POSIX functions
#endif

#include "../include/graphics.h"
#include "../include/p_bar.h"

void hide_cursor() {
	printf("\033[?25l");  // ANSI sequence to hide cursor
}

void show_cursor() {
	printf("\033[?25h");  // ANSI sequence to show cursor
}

void clear_screen()
{
	// Clears the entire screen
	printf("\033[2J");
	// Clear print history
	printf("\033[3J");
	// Moves the cursor to home position (0,0)
	printf("\033[H");
}

void calculate_terminal_dimensions(Terminal *details)
{
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		details->t_cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		details->t_rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	else
	{
		details->t_rows = 25;
		details->t_cols = 80;
	}
#else
	struct winsize window;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	details->t_rows = window.ws_row;
	details->t_cols = window.ws_col;
#endif
}

void calculate_center_position(Terminal details, int *start_row, int *start_col)
{
	*start_col = (details.t_cols - 17) / 2;
	*start_row = (details.t_rows - 5) / 2;
}

void draw_box(int start_row, int start_col)
{
	// Position cursor and draw top border
	printf("\033[%d;%dH", start_row, start_col);
	printf("┌───────────────┐");

	// Draw sides
	printf("\033[%d;%dH", start_row + 1, start_col);
	printf("│               │"); // spacing row
	printf("\033[%d;%dH", start_row + 2, start_col);
	printf("│               │"); // time is displayed here
	printf("\033[%d;%dH", start_row + 3, start_col);
	printf("│               │"); // spacing row
	printf("\033[%d;%dH", start_row + 4, start_col);
	printf("│               │"); // p-bar percentage 
	printf("\033[%d;%dH", start_row + 5, start_col);
	printf("│               │"); // p-bar
	printf("\033[%d;%dH", start_row + 6, start_col);
	printf("│               │"); // spacing row

	// Draw bottom
	printf("\033[%d;%dH", start_row + 7, start_col);
	printf("└───────────────┘");
}

void draw_p_bar(p_bar bar, int start_row, int start_col) {
	printf("\033[%d;%dH", start_row + 4, start_col + 7);
	printf("%2d%%", bar.percentages);
	for (int i = 0; i < 13; i++) {
		printf("\033[%d;%dH", start_row + 5, start_col + i + 2);
		if (i >= bar.filled) {
			printf("-");
			fflush(stdout);
		} else {
			printf("█");
			fflush(stdout);
		}
	}
}

void draw_end_box(Terminal ter, int start_row, int start_col) {
	draw_box(start_row, start_col);
	printf("\033[%d;%dH", start_row + 2, start_col + 2);
	printf("Timer is done");
	printf("\033[%d;%dH", start_row + 4, start_col + 6);
	printf("100%%");
	printf("\033[%d;%dH", start_row + 5, start_col + 2);
	printf("█████████████");
	fflush(stdout);
	show_cursor();
	printf("\033[%d;1H", ter.t_rows);
}