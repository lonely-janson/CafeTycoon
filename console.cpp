#include "console.hpp"
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 65
#define HEIGHT 25

int Console::linux_getch(void) {
    int ch;
    struct termios buf, save;
    tcgetattr(0, &save);
    buf = save;
    buf.c_lflag &= ~(ICANON | ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);

    return ch;
}

const char *Console::input(int mode, int maxsize) {
    char *ch = new char[maxsize];
    int index = 0;

    while (1) {
        ch[index] = Console::linux_getch();
        if (ch[index] == BACK) {
            cout << "\b \b";
            index--;
        } else if (ch[index] == ENTER) {
            cout << ch[index];
            break;
        } else if (index < maxsize) {
            (mode == 0) ? cout << ch[index] : cout << '*';
            index++;
        }
    }

    ch[index] = '\0';

    return ch;
}

void Console::gotoXY(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

void Console::printColorString(const char *str, int color) {
    printf("\033[%dm%s\033[0m", color, str);
}

void Console::setBackground(int color) {
    color += 10;
    printf("\033[%dm", color);
}

void Console::printDot(int x, int y, int color) {
    gotoXY(x, y);
    setBackground(color);
    printColorString(" ");
}

void Console::gotoEnd() { gotoXY(1, HEIGHT + 1); }
