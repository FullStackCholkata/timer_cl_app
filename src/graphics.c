#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // For Windows-specific console functions
#else
#include <sys/ioctl.h> // For getting terminal size
#include <unistd.h>	   // For STDOUT_FILENO and other POSIX functions
#endif

#include "../include/graphics.h"

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
	printf("│               │");
	printf("\033[%d;%dH", start_row + 2, start_col);
	printf("│               │");
	printf("\033[%d;%dH", start_row + 3, start_col);
	printf("│               │");

	// Draw bottom
	printf("\033[%d;%dH", start_row + 4, start_col);
	printf("└───────────────┘");
}

// Maybe the box should be a fixed size.
// It doesn't really make sense to change the size when the timer always stays the same HH:MM:SS