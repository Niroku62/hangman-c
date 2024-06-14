#ifndef ANSI_CODES_H
#define ANSI_CODES_H

#include "os_check.h"

#include <stdio.h>

// ANSI Control Sequence Introducer
#define M_ANSI_CSI           "\033["

// Action Commands
#define M_ANSI_SET_COLOR     "m"
#define M_ANSI_SET_FG_NORMAL "3"
#define M_ANSI_SET_BG_NORMAL "4"
#define M_ANSI_SET_FG_BRIGHT "9"
#define M_ANSI_SET_BG_BRIGHT "10"
#define M_ANSI_CLEAR_SCREEN  "J"
#define M_ANSI_CLEAR_LINE    "K"

// Foreground (text) colors
#define FGN_BLACK             M_ANSI_CSI M_ANSI_SET_FG_NORMAL "0" M_ANSI_SET_COLOR
#define FGN_RED               M_ANSI_CSI M_ANSI_SET_FG_NORMAL "1" M_ANSI_SET_COLOR
#define FGN_GREEN             M_ANSI_CSI M_ANSI_SET_FG_NORMAL "2" M_ANSI_SET_COLOR
#define FGN_YELLOW            M_ANSI_CSI M_ANSI_SET_FG_NORMAL "3" M_ANSI_SET_COLOR
#define FGN_BLUE              M_ANSI_CSI M_ANSI_SET_FG_NORMAL "4" M_ANSI_SET_COLOR
#define FGN_MAGENTA           M_ANSI_CSI M_ANSI_SET_FG_NORMAL "5" M_ANSI_SET_COLOR
#define FGN_CYAN              M_ANSI_CSI M_ANSI_SET_FG_NORMAL "6" M_ANSI_SET_COLOR
#define FGN_WHITE             M_ANSI_CSI M_ANSI_SET_FG_NORMAL "7" M_ANSI_SET_COLOR

// Bright foreground colors
#define FGB_BLACK             M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "0" M_ANSI_SET_COLOR
#define FGB_RED               M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "1" M_ANSI_SET_COLOR
#define FGB_GREEN             M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "2" M_ANSI_SET_COLOR
#define FGB_YELLOW            M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "3" M_ANSI_SET_COLOR
#define FGB_BLUE              M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "4" M_ANSI_SET_COLOR
#define FGB_MAGENTA           M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "5" M_ANSI_SET_COLOR
#define FGB_CYAN              M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "6" M_ANSI_SET_COLOR
#define FGB_WHITE             M_ANSI_CSI M_ANSI_SET_FG_BRIGHT "7" M_ANSI_SET_COLOR

// Background colors
#define BGN_BLACK             M_ANSI_CSI M_ANSI_SET_BG_NORMAL "0" M_ANSI_SET_COLOR
#define BGN_RED               M_ANSI_CSI M_ANSI_SET_BG_NORMAL "1" M_ANSI_SET_COLOR
#define BGN_GREEN             M_ANSI_CSI M_ANSI_SET_BG_NORMAL "2" M_ANSI_SET_COLOR
#define BGN_YELLOW            M_ANSI_CSI M_ANSI_SET_BG_NORMAL "3" M_ANSI_SET_COLOR
#define BGN_BLUE              M_ANSI_CSI M_ANSI_SET_BG_NORMAL "4" M_ANSI_SET_COLOR
#define BGN_MAGENTA           M_ANSI_CSI M_ANSI_SET_BG_NORMAL "5" M_ANSI_SET_COLOR
#define BGN_CYAN              M_ANSI_CSI M_ANSI_SET_BG_NORMAL "6" M_ANSI_SET_COLOR
#define BGN_WHITE             M_ANSI_CSI M_ANSI_SET_BG_NORMAL "7" M_ANSI_SET_COLOR

// Bright background colors
#define BGB_BLACK             M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "0" M_ANSI_SET_COLOR
#define BGB_RED               M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "1" M_ANSI_SET_COLOR
#define BGB_GREEN             M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "2" M_ANSI_SET_COLOR
#define BGB_YELLOW            M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "3" M_ANSI_SET_COLOR
#define BGB_BLUE              M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "4" M_ANSI_SET_COLOR
#define BGB_MAGENTA           M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "5" M_ANSI_SET_COLOR
#define BGB_CYAN              M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "6" M_ANSI_SET_COLOR
#define BGB_WHITE             M_ANSI_CSI M_ANSI_SET_BG_BRIGHT "7" M_ANSI_SET_COLOR

// Reset all attributes to their defaults
#define ANSI_RESET            M_ANSI_CSI "0" M_ANSI_SET_COLOR

// Cursor Control
#define CURSOR_UP(N)          M_ANSI_CSI #N "A"
#define CURSOR_DOWN(N)        M_ANSI_CSI #N "B"
#define CURSOR_FORWARD(N)     M_ANSI_CSI #N "C"
#define CURSOR_BACKWARD(N)    M_ANSI_CSI #N "D"
#define CURSOR_SET(Y, X)      M_ANSI_CSI #Y ";" #X "H"
#define CURSOR_HIDE           M_ANSI_CSI "?25l"
#define CURSOR_SHOW           M_ANSI_CSI "?25h"

// Screen and Line Clearing
#define CLEAR_SCREEN          M_ANSI_CSI "2" M_ANSI_CLEAR_SCREEN
#define CLEAR_TO_SCREEN_END   M_ANSI_CSI "0" M_ANSI_CLEAR_SCREEN
#define CLEAR_TO_SCREEN_START M_ANSI_CSI "1" M_ANSI_CLEAR_SCREEN
#define CLEAR_LINE            M_ANSI_CSI "2" M_ANSI_CLEAR_LINE
#define CLEAR_TO_LINE_END     M_ANSI_CSI "0" M_ANSI_CLEAR_LINE
#define CLEAR_TO_LINE_START   M_ANSI_CSI "1" M_ANSI_CLEAR_LINE

#if defined(IS_LINUX)

void ansi_codes_enable() {}

#elif defined(IS_WINDOWS)

#include <windows.h>

void ansi_codes_enable() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) {
		return;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) {
		return;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

#endif // os linux/windows

#endif // #ifndef ANSI_CODES_H

