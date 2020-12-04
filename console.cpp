#include "console.hpp"
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 65
#define HEIGHT 25

int Console::x;
int Console::y;

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
    printf("\033[%dm", BLACK);
    fflush(stdout);
    if (mode != 3) {
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
    } else {
        while (1) {
            ch[index] = Console::linux_getch();
            if (ch[index] == BACK) {
                cout << "\b \b";
                index--;
            } else if (ch[index] == ENTER) {
                cout << ch[index];
                break;
            } else if (ch[index] >= '0' && ch[index] <= '9') {
                if (index < maxsize) {
                    cout << ch[index];
                    index++;
                }
            }
        }
    }

    ch[index] = '\0';
    printf("\033[0m");

    return ch;
}

void Console::gotoXY(int _x, int _y) {
    x = _x;
    y = _y;
    printf("\033[%d;%df", _y, _x);
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

void Console::drawCursor(int _x, int _y, int color, int backColor) {
    backColor += 10;
    printf("\033[%dm\b ", backColor);
    gotoXY(_x, _y);
    printf("\033[%dm>", color);
}
