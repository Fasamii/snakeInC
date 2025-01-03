#include <termios.h>
#include <sys/select.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <time.h>
#include <fcntl.h>
// internal //
#include "./typedef.h"

char kbHit () {
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(STDIN_FILENO, &fd);
	select(STDIN_FILENO + 1, &fd, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fd);
}

void initTerm() {
	printf("\e[?1049h");
	printf("\e[H\e[J");
	printf("\e[?25l");
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_cc[VMIN] = 1;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	fflush(stdout);
}

void stopTerm() {
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	printf("\e[?1049l");
	printf("\x1B[?25h");
	printf("\e[?25h");
}

Vec getTermSize() {
	struct winsize win_size;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &win_size);
	Vec size;
	size.x = win_size.ws_row;
	size.y = win_size.ws_col;
	return size;
}
