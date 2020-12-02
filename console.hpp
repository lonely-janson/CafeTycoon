#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

#include <stdio.h>
#include <string>

#define BACK 127
#define ENTER 10
#define SPACE 32
#define UP 279165
#define DOWN 279166
#define RIGHT 279167
#define LEFT 279168

// 색상
#define BLACK 30
#define RED 31
#define GREEN 32
#define YELLOW 33
#define BLUE 34
#define MAGENTA 35
#define CYAN 36
#define LIGHTGRAY 37
#define GRAY 90
#define LIGHTRED 91
#define LIGHTGREEN 92
#define LIGHTYELLOW 93
#define LIGHTBLUE 94
#define LIGHTMAGENTA 95
#define LIGHTCYAN 96

using namespace std;

class Console {
  private:
    static int x;
    static int y;

  public:
    static int linux_getch(void);
    static int getX() { return x; }   // 현재 x 좌표
    static int getY() { return y; }   // 현재 y 좌표
    static void gotoXY(int x, int y); // x,y 좌표 변경
    static void tempGotoXY(int _x, int _y);
    static void gotoEnd();
    static void
    printColorString(const char *str,
                     int color = 39); // 글씨색 변경 Default : 기본색
    static void setBackground(int color = 49); // 배경색 변경 Default : 기본색
    static void printDot(int x, int y, int color);
    static const char *
    input(int mode = 0, int maxsize = 20); // mode 0 : 일반입력, 1 : 비밀번호
    static void drawCursor(int _x, int _y, int backColor, int color);
};

#endif //__CONSOLE_HPP__
