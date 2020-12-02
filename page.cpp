#include "page.hpp"
#include <string>

void Page::clear() { system("clear"); }

void Page::frame() {
    clear();
    for (int i = 1; i <= WIDTH; i++) {      //가로
        for (int j = 1; j <= HEIGHT; j++) { //세로
            Console::gotoXY(i, j);
            if (i == 1 || i == WIDTH || j == 1 || j == HEIGHT || i == 2 ||
                i == WIDTH - 1)
                Console::setBackground(LIGHTMAGENTA); //테두리
            else
                Console::setBackground(LIGHTGRAY);
            Console::printColorString(" ");
        }
    }
}

void Page::startPage() {
    clear();
    for (int i = 1; i <= WIDTH; i++) {      //가로
        for (int j = 1; j <= HEIGHT; j++) { //세로
            Console::gotoXY(i, j);
            if (i == 1 || i == WIDTH || j == 1 || j == HEIGHT || i == 2 ||
                i == WIDTH - 1)
                Console::setBackground(LIGHTGRAY); //테두리
            else
                Console::setBackground(LIGHTMAGENTA);
            Console::printColorString(" ");
        }
    }

    // c
    Console::printDot(11, 5, LIGHTGRAY);
    Console::printDot(12, 5, LIGHTGRAY);
    Console::printDot(10, 6, LIGHTGRAY);
    Console::printDot(10, 7, LIGHTGRAY);
    Console::printDot(10, 8, LIGHTGRAY);
    Console::printDot(11, 9, LIGHTGRAY);
    Console::printDot(12, 9, LIGHTGRAY);
    // a
    Console::printDot(15, 9, LIGHTGRAY);
    Console::printDot(15, 8, LIGHTGRAY);
    Console::printDot(15, 7, LIGHTGRAY);
    Console::printDot(15, 6, LIGHTGRAY);
    Console::printDot(16, 5, LIGHTGRAY);
    Console::printDot(17, 5, LIGHTGRAY);
    Console::printDot(18, 5, LIGHTGRAY);
    Console::printDot(19, 6, LIGHTGRAY);
    Console::printDot(19, 7, LIGHTGRAY);
    Console::printDot(19, 8, LIGHTGRAY);
    Console::printDot(19, 9, LIGHTGRAY);
    Console::printDot(16, 7, LIGHTGRAY);
    Console::printDot(17, 7, LIGHTGRAY);
    Console::printDot(18, 7, LIGHTGRAY);
    // f
    Console::printDot(22, 5, LIGHTGRAY);
    Console::printDot(22, 6, LIGHTGRAY);
    Console::printDot(22, 7, LIGHTGRAY);
    Console::printDot(22, 8, LIGHTGRAY);
    Console::printDot(22, 9, LIGHTGRAY);
    for (int i = 23; i < 26; i++)
        Console::printDot(i, 5, LIGHTGRAY);
    for (int i = 23; i < 26; i++)
        Console::printDot(i, 7, LIGHTGRAY);
    // e
    Console::printDot(28, 5, LIGHTGRAY);
    Console::printDot(28, 6, LIGHTGRAY);
    Console::printDot(28, 7, LIGHTGRAY);
    Console::printDot(28, 8, LIGHTGRAY);
    Console::printDot(28, 9, LIGHTGRAY);
    for (int i = 29; i < 32; i++)
        Console::printDot(i, 5, LIGHTGRAY);
    for (int i = 29; i < 32; i++)
        Console::printDot(i, 7, LIGHTGRAY);
    for (int i = 29; i < 32; i++)
        Console::printDot(i, 9, LIGHTGRAY);
    // t
    Console::printDot(15, 16, LIGHTGRAY);
    for (int i = 16; i < 20; i++)
        Console::printDot(i, 16, LIGHTGRAY);
    for (int i = 17; i < 21; i++)
        Console::printDot(17, i, LIGHTGRAY);
    // y
    Console::printDot(22, 16, LIGHTGRAY);
    Console::printDot(22, 17, LIGHTGRAY);
    Console::printDot(22, 18, LIGHTGRAY);
    Console::printDot(23, 18, LIGHTGRAY);
    Console::printDot(24, 18, LIGHTGRAY);
    Console::printDot(24, 19, LIGHTGRAY);
    Console::printDot(24, 20, LIGHTGRAY);
    Console::printDot(25, 18, LIGHTGRAY);
    Console::printDot(26, 18, LIGHTGRAY);
    Console::printDot(26, 17, LIGHTGRAY);
    Console::printDot(26, 16, LIGHTGRAY);
    // c
    Console::printDot(30, 16, LIGHTGRAY);
    Console::printDot(31, 16, LIGHTGRAY);
    Console::printDot(29, 17, LIGHTGRAY);
    Console::printDot(29, 18, LIGHTGRAY);
    Console::printDot(29, 19, LIGHTGRAY);
    Console::printDot(30, 20, LIGHTGRAY);
    Console::printDot(31, 20, LIGHTGRAY);
    // o
    Console::printDot(35, 16, LIGHTGRAY);
    Console::printDot(36, 16, LIGHTGRAY);
    Console::printDot(34, 17, LIGHTGRAY);
    Console::printDot(34, 18, LIGHTGRAY);
    Console::printDot(34, 19, LIGHTGRAY);
    Console::printDot(35, 20, LIGHTGRAY);
    Console::printDot(36, 20, LIGHTGRAY);
    Console::printDot(37, 19, LIGHTGRAY);
    Console::printDot(37, 18, LIGHTGRAY);
    Console::printDot(37, 17, LIGHTGRAY);
    // o
    Console::printDot(41, 16, LIGHTGRAY);
    Console::printDot(42, 16, LIGHTGRAY);
    Console::printDot(40, 17, LIGHTGRAY);
    Console::printDot(40, 18, LIGHTGRAY);
    Console::printDot(40, 19, LIGHTGRAY);
    Console::printDot(41, 20, LIGHTGRAY);
    Console::printDot(42, 20, LIGHTGRAY);
    Console::printDot(43, 19, LIGHTGRAY);
    Console::printDot(43, 18, LIGHTGRAY);
    Console::printDot(43, 17, LIGHTGRAY);
    // n
    for (int i = 16; i < 21; i++)
        Console::printDot(46, i, LIGHTGRAY);
    Console::printDot(47, 17, LIGHTGRAY);
    Console::printDot(48, 18, LIGHTGRAY);
    Console::printDot(49, 19, LIGHTGRAY);
    Console::printDot(50, 20, LIGHTGRAY);
    for (int i = 16; i < 21; i++)
        Console::printDot(50, i, LIGHTGRAY);

    Console::gotoEnd();
}

void Page::login() {
    frame();

    // i
    for (int i = 8; i < 12; i++)
        Console::printDot(14, i, LIGHTBLUE);
    for (int i = 12; i < 17; i++)
        Console::printDot(i, 8, LIGHTBLUE);
    for (int i = 12; i < 17; i++)
        Console::printDot(i, 11, LIGHTBLUE);
    // d
    for (int i = 8; i < 12; i++)
        Console::printDot(21, i, LIGHTBLUE);
    Console::printDot(22, 8, LIGHTBLUE);
    Console::printDot(23, 8, LIGHTBLUE);
    Console::printDot(24, 9, LIGHTBLUE);
    Console::printDot(24, 10, LIGHTBLUE);
    Console::printDot(23, 11, LIGHTBLUE);
    Console::printDot(22, 11, LIGHTBLUE);

    // p
    for (int i = 14; i < 18; i++)
        Console::printDot(12, i, LIGHTBLUE);
    Console::printDot(13, 14, LIGHTBLUE);
    Console::printDot(14, 14, LIGHTBLUE);
    Console::printDot(15, 15, LIGHTBLUE);
    Console::printDot(14, 16, LIGHTBLUE);
    Console::printDot(13, 16, LIGHTBLUE);
    // w
    Console::printDot(17, 14, LIGHTBLUE);
    Console::printDot(17, 15, LIGHTBLUE);
    Console::printDot(18, 16, LIGHTBLUE);
    Console::printDot(19, 17, LIGHTBLUE);
    Console::printDot(20, 16, LIGHTBLUE);
    Console::printDot(21, 15, LIGHTBLUE);
    Console::printDot(22, 16, LIGHTBLUE);
    Console::printDot(23, 17, LIGHTBLUE);
    Console::printDot(24, 16, LIGHTBLUE);
    Console::printDot(25, 15, LIGHTBLUE);
    Console::printDot(25, 14, LIGHTBLUE);

    for (int i = 30; i < 50; i++) {
        Console::printDot(i, 11, GRAY);
        Console::printDot(i, 17, GRAY);
    }

    // sign up | login
    Console::gotoXY(14, 22);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("SIGN UP", LIGHTMAGENTA);
    Console::gotoXY(33, 22);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("/", LIGHTMAGENTA);
    Console::gotoXY(46, 22);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("LOGIN", LIGHTMAGENTA);

    Console::gotoEnd();
}

// void Page::signUp() {}

void Page::mainPage() {
    frame();

    // STORE
    for (int i = 50; i < 53; i++) {
        Console::printDot(i, 9, LIGHTGREEN);
        Console::printDot(i, 8, LIGHTGREEN);
    }
    Console::printDot(53, 9, GRAY);
    Console::printDot(54, 9, GRAY);
    Console::printDot(53, 8, GRAY);
    Console::printDot(54, 8, GRAY);
    for (int i = 55; i < 58; i++) {
        Console::printDot(i, 9, LIGHTGREEN);
        Console::printDot(i, 8, LIGHTGREEN);
    }
    for (int i = 50; i < 58; i++) {
        Console::printDot(i, 7, LIGHTGREEN);
        Console::printDot(i, 4, LIGHTRED);
    }
    for (int i = 48; i < 60; i++)
        Console::printDot(i, 6, LIGHTRED);
    for (int i = 49; i < 59; i++)
        Console::printDot(i, 5, LIGHTYELLOW);
    Console::gotoXY(50, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("  STORE", GREEN);

    // MY INFO
    for (int i = 50; i < 58; i++)
        Console::printDot(i, 17, LIGHTGRAY);
    for (int i = 51; i < 57; i++)
        Console::printDot(i, 18, LIGHTGRAY);
    for (int i = 52; i < 56; i++)
        Console::printDot(i, 19, LIGHTGRAY);
    for (int i = 50; i < 58; i++)
        for (int j = 20; j < 23; j++)
            Console::printDot(i, j, LIGHTBLUE);
    for (int i = 50; i < 58; i++)
        for (int j = 15; j < 17; j++)
            Console::printDot(i, j, BLACK);
    Console::printDot(50, 17, BLACK);
    Console::printDot(50, 18, BLACK);
    Console::printDot(57, 17, BLACK);
    Console::printDot(57, 18, BLACK);
    Console::printDot(50, 19, BLACK);
    Console::printDot(51, 19, BLACK);
    Console::printDot(57, 19, BLACK);
    Console::printDot(56, 19, BLACK);
    Console::printDot(50, 20, BLACK);
    Console::printDot(57, 20, BLACK);
    Console::printDot(52, 19, BLACK);
    Console::printDot(55, 19, BLACK);
    Console::printDot(51, 20, BLACK);
    Console::printDot(56, 20, BLACK);
    Console::printDot(50, 21, BLACK);
    Console::printDot(57, 21, BLACK);
    Console::gotoXY(52, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(".", BLACK);
    Console::gotoXY(55, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(".", BLACK);
    Console::gotoXY(53, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("__", BLACK);
    Console::gotoXY(51, 23);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("MY INFO", BLUE);

    // RANKING
    for (int i = 8; i < 23; i++)
        for (int j = 19; j < 21; j++)
            Console::printDot(i, j, LIGHTYELLOW);
    for (int i = 9; i < 22; i++)
        Console::printDot(i, 21, LIGHTYELLOW);
    for (int i = 10; i < 21; i++)
        Console::printDot(i, 22, LIGHTYELLOW);
    Console::printDot(9, 18, LIGHTYELLOW);
    Console::printDot(10, 18, LIGHTYELLOW);
    Console::printDot(20, 18, LIGHTYELLOW);
    Console::printDot(21, 18, LIGHTYELLOW);
    for (int i = 13; i < 18; i++) {
        Console::printDot(i, 18, LIGHTYELLOW);
        Console::printDot(i, 16, LIGHTYELLOW);
    }
    for (int i = 15; i < 18; i++)
        Console::printDot(15, i, LIGHTYELLOW);
    Console::printDot(15, 16, LIGHTCYAN);
    Console::printDot(15, 18, MAGENTA);
    Console::printDot(15, 19, MAGENTA);
    Console::printDot(13, 19, MAGENTA);
    Console::printDot(14, 19, MAGENTA);
    Console::printDot(13, 20, MAGENTA);
    for (int i = 14; i < 18; i++)
        Console::printDot(i, 20, LIGHTMAGENTA);
    Console::printDot(16, 19, LIGHTMAGENTA);
    Console::printDot(17, 19, LIGHTMAGENTA);
    for (int i = 13; i < 18; i++)
        Console::printDot(i, 21, LIGHTMAGENTA);
    Console::printDot(10, 19, MAGENTA);
    Console::printDot(10, 20, MAGENTA);
    Console::printDot(9, 19, LIGHTMAGENTA);
    Console::printDot(9, 20, LIGHTMAGENTA);
    Console::printDot(10, 21, LIGHTMAGENTA);
    Console::printDot(20, 19, MAGENTA);
    Console::printDot(20, 20, MAGENTA);
    Console::printDot(21, 19, LIGHTMAGENTA);
    Console::printDot(21, 20, LIGHTMAGENTA);
    Console::printDot(20, 21, LIGHTMAGENTA);
    Console::gotoXY(11, 23);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" RANKING", CYAN);

    // MINI GAME
    Console::gotoXY(6, 7);
    Console::setBackground(GRAY);
    Console::printColorString("◀     ▶ ", LIGHTGRAY);
    Console::gotoXY(9, 6);
    Console::setBackground(GRAY);
    Console::printColorString("▲ ", GRAY);
    Console::gotoXY(9, 5);
    Console::setBackground(GRAY);
    Console::printColorString("▲ ", LIGHTGRAY);
    Console::gotoXY(9, 8);
    Console::setBackground(GRAY);
    Console::printColorString("▲ ", GRAY);
    Console::gotoXY(9, 9);
    Console::setBackground(GRAY);
    Console::printColorString("▼ ", LIGHTGRAY);
    Console::gotoXY(17, 6);
    Console::setBackground(LIGHTRED);
    Console::printColorString(" X ", LIGHTGRAY);
    Console::gotoXY(22, 6);
    Console::setBackground(BLUE);
    Console::printColorString(" A ", LIGHTGRAY);
    Console::gotoXY(17, 8);
    Console::setBackground(GREEN);
    Console::printColorString(" Y ", LIGHTGRAY);
    Console::gotoXY(22, 8);
    Console::setBackground(YELLOW);
    Console::printColorString(" B ", LIGHTGRAY);
    Console::gotoXY(11, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" MINI GAME", GRAY);

    // PLAY
    for (int i = 24; i < 45; i++)
        for (int j = 11; j < 16; j++)
            Console::printDot(i, j, BLACK);
    // P
    for (int i = 11; i < 16; i++)
        Console::printDot(24, i, LIGHTMAGENTA);
    for (int i = 25; i < 28; i++) {
        Console::printDot(i, 11, LIGHTMAGENTA);
        Console::printDot(i, 13, LIGHTMAGENTA);
    }
    Console::printDot(27, 12, LIGHTMAGENTA);
    // L
    for (int i = 11; i < 16; i++)
        Console::printDot(29, i, LIGHTBLUE);
    for (int i = 30; i < 33; i++)
        Console::printDot(i, 15, LIGHTBLUE);
    // A
    for (int i = 11; i < 16; i++) {
        Console::printDot(34, i, LIGHTMAGENTA);
        Console::printDot(37, i, LIGHTMAGENTA);
    }
    for (int i = 35; i < 37; i++) {
        Console::printDot(i, 13, LIGHTMAGENTA);
        Console::printDot(i, 11, LIGHTMAGENTA);
    }
    // Y
    for (int i = 11; i < 14; i++) {
        Console::printDot(39, i, LIGHTBLUE);
        Console::printDot(44, i, LIGHTBLUE);
    }
    for (int i = 40; i < 44; i++)
        Console::printDot(i, 13, LIGHTBLUE);
    for (int i = 14; i < 16; i++)
        Console::printDot(41, i, LIGHTBLUE);

    Console::gotoEnd();
}

void Page::workingPage1(map<int, int> &orderd) {
    frame();
    int i;

    for (int i = 3; i < WIDTH - 1; i++)
        for (int j = 17; j < HEIGHT; j++)
            Console::printDot(i, j, GRAY);

    for (int i = 7; i < 19; i++)
        for (int j = 5; j < 17; j++)
            Console::printDot(i, j, BLACK);

    for (int i = 8; i < 18; i++)
        for (int j = 8; j < 11; j++)
            Console::printDot(i, j, LIGHTGRAY);

    for (int i = 11; i < 15; i++)
        for (int j = 11; j < 13; j++)
            Console::printDot(i, j, LIGHTGRAY);

    Console::gotoXY(10, 9);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("|    |", BLACK);

    Console::gotoXY(11, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" ㅁ  ", BLACK);

    for (int i = 10; i < 16; i++)
        Console::printDot(i, 13, LIGHTRED);

    for (int i = 9; i < 17; i++)
        Console::printDot(i, 14, LIGHTRED);

    for (int i = 8; i < 18; i++)
        Console::printDot(i, 15, LIGHTRED);

    for (int i = 7; i < 19; i++)
        Console::printDot(i, 16, LIGHTRED);

    for (int i = 7; i > 5; i--)
        Console::printDot(25, i, LIGHTBLUE);

    Console::printDot(24, 8, LIGHTBLUE);
    Console::printDot(23, 9, LIGHTBLUE);
    Console::printDot(22, 10, LIGHTBLUE);
    Console::printDot(23, 11, LIGHTBLUE);
    Console::printDot(24, 12, LIGHTBLUE);

    for (int i = 13; i < 15; i++)
        Console::printDot(25, i, LIGHTBLUE);

    for (int i = 26; i < 56; i++) {
        Console::printDot(i, 6, LIGHTBLUE);
        Console::printDot(i, 14, LIGHTBLUE);
    }
    for (int i = 6; i < 15; i++)
        Console::printDot(55, i, LIGHTBLUE);

    Console::gotoXY(27, 8);
    for (i = 0, iter = orderd.begin(); iter != orderd.end(); iter++, i++) {
        string temp = coffeeName[iter->first] + to_string(iter->second) + "잔 ";
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(temp.c_str(), MAGENTA);
        if (i % 2 == 1) {
            Console::gotoXY(27, 10);
        }
    }
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("\b 주세요", MAGENTA);

    Console::gotoEnd();
}

void Page::makingDrink(map<int, int> &orderd, int level) {
    if (level > 5)
        level = 5;
    frame();
    int i;

    Console::gotoXY(4, 3);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("총 주문 음료 : ", MAGENTA);

    for (i = 0, iter = orderd.begin(); iter != orderd.end(); iter++, i++) {
        string temp =
            coffeeName[iter->first] + " " + to_string(iter->second) + "잔 ";
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(temp.c_str(), MAGENTA);
        if (i % 2 == 1) {
            Console::gotoXY(19, 4);
        }
    }

    Console::gotoXY(4, 5);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("현재 제조 중인 음료 : ", MAGENTA);
    Console::gotoXY(50, 3);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("현재 만든", MAGENTA);
    Console::gotoXY(50, 4);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("음료 수 (0/0)", MAGENTA);
    for (int i = 49; i < WIDTH; i++)
        Console::printDot(i, 5, LIGHTMAGENTA);

    for (int i = 4; i < 45; i++)
        Console::printDot(i, 10, GRAY);

    for (int i = 7; i < 24; i++) {
        Console::printDot(13, i, GRAY);
        Console::printDot(24, i, GRAY);
        Console::printDot(35, i, GRAY);
    }
    Console::gotoXY(6, 8);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" 샷", LIGHTRED);
    Console::gotoXY(15, 8);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" 베이스", GREEN);
    Console::gotoXY(26, 8);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("  시럽", YELLOW);
    Console::gotoXY(37, 8);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" 재료", CYAN);

    Console::gotoXY(50, 8);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("선택된 재료", BLUE);
    for (int i = 49; i < WIDTH - 1; i++)
        Console::printDot(i, 9, LIGHTBLUE);

    for (int i = 49; i < WIDTH - 2; i++)
        for (int j = 19; j < 24; j++) {
            if (i == 49 || i == WIDTH - 3 || j == 19 || j == 23)
                Console::printDot(i, j, GRAY);
            else
                Console::printDot(i, j, LIGHTYELLOW);
        }
    Console::gotoXY(52, 21);
    Console::setBackground(LIGHTYELLOW);
    Console::printColorString("만들기!!", GRAY);

    //샷 재료 보이기
    for (int i = 0; i < 3; i++) {
        Console::gotoXY(6, 12 + (i * 2));
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(ingerdients[0][i].c_str(), MAGENTA);
    }

    //베이스 재료 보이기
    for (int i = 0; i < 2; i++) {
        Console::gotoXY(15, 12 + (i * 2));
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(ingerdients[1][i].c_str(), MAGENTA);
    }

    if (level > 3) {
        Console::gotoXY(15, 16);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(ingerdients[1][2].c_str(), MAGENTA);
    }

    //시럽 재료 보이기
    for (int i = 0; i < level - 2; i++) {
        Console::gotoXY(26, 12 + (i * 2));
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(ingerdients[2][i].c_str(), MAGENTA);
    }

    //기타 재료 보이기
    for (int i = 0; i < level - 2; i++) {
        Console::gotoXY(37, 12 + (i * 2));
        Console::setBackground(LIGHTGRAY);
        Console::printColorString(ingerdients[3][i].c_str(), MAGENTA);
    }

    //커서색 변경하기
    Console::gotoXY(4, 12);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(">", RED);
}

void Page::workingPage2() {
    frame();
    for (int i = 3; i < WIDTH - 1; i++)
        for (int j = 17; j < HEIGHT; j++)
            Console::printDot(i, j, GRAY);
    for (int i = 52; i < 58; i++)
        Console::printDot(i, 10, LIGHTYELLOW);
    for (int i = 51; i < 59; i++)
        Console::printDot(i, 11, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 12, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 13, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        for (int j = 14; j < 18; j++)
            Console::printDot(i, j, LIGHTYELLOW);
    for (int i = 52; i < 58; i++)
        for (int j = 18; j < 20; j++)
            Console::printDot(i, j, LIGHTMAGENTA);
    Console::printDot(51, 18, LIGHTMAGENTA);
    Console::printDot(50, 19, LIGHTMAGENTA);
    Console::printDot(49, 20, LIGHTGRAY);
    Console::printDot(58, 18, LIGHTMAGENTA);
    Console::printDot(59, 19, LIGHTMAGENTA);
    Console::printDot(60, 20, LIGHTGRAY);
    for (int i = 52; i < 58; i++)
        for (int j = 20; j < 24; j++) {
            Console::printDot(i, j, LIGHTBLUE);
        }
    Console::printDot(52, 24, BLACK);
    Console::printDot(53, 24, BLACK);
    Console::printDot(57, 24, BLACK);
    Console::printDot(56, 24, BLACK);

    //말풍선
    for (int i = 7; i > 5; i--)
        Console::printDot(42, i, LIGHTBLUE);
    Console::printDot(43, 8, LIGHTBLUE);
    Console::printDot(44, 9, LIGHTBLUE);
    Console::printDot(45, 10, LIGHTBLUE);
    Console::printDot(44, 11, LIGHTBLUE);
    Console::printDot(43, 12, LIGHTBLUE);
    for (int i = 13; i < 15; i++)
        Console::printDot(42, i, LIGHTBLUE);
    for (int i = 42; i > 16; i--) {
        Console::printDot(i, 6, LIGHTBLUE);
        Console::printDot(i, 14, LIGHTBLUE);
    }
    for (int i = 6; i < 15; i++)
        Console::printDot(16, i, LIGHTBLUE);
    Console::gotoXY(18, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("주문하신 음료 나왔습니다~", BLUE);
    Console::gotoEnd();
}

void Page::workingPage3() {
    frame();

    for (int i = 3; i < WIDTH - 1; i++)
        for (int j = 17; j < HEIGHT; j++)
            Console::printDot(i, j, GRAY);
    for (int i = 52; i < 58; i++)
        Console::printDot(i, 10, LIGHTYELLOW);
    for (int i = 51; i < 59; i++)
        Console::printDot(i, 11, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 12, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 13, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        for (int j = 14; j < 18; j++)
            Console::printDot(i, j, LIGHTYELLOW);
    for (int i = 52; i < 58; i++)
        for (int j = 18; j < 20; j++)
            Console::printDot(i, j, LIGHTMAGENTA);
    Console::printDot(51, 18, LIGHTMAGENTA);
    Console::printDot(50, 19, LIGHTMAGENTA);
    Console::printDot(49, 20, LIGHTGRAY);
    Console::printDot(58, 18, LIGHTMAGENTA);
    Console::printDot(59, 19, LIGHTMAGENTA);
    Console::printDot(60, 20, LIGHTGRAY);
    for (int i = 52; i < 58; i++)
        for (int j = 20; j < 24; j++) {
            Console::printDot(i, j, LIGHTBLUE);
        }
    Console::printDot(52, 24, BLACK);
    Console::printDot(53, 24, BLACK);
    Console::printDot(57, 24, BLACK);
    Console::printDot(56, 24, BLACK);

    //손님
    for (int i = 8; i < 18; i++)
        for (int j = 7; j < 17; j++)
            Console::printDot(i, j, BLACK);

    for (int i = 9; i < 17; i++)
        for (int j = 10; j < 12; j++)
            Console::printDot(i, j, LIGHTGRAY);

    for (int i = 11; i < 15; i++)
        for (int j = 12; j < 14; j++)
            Console::printDot(i, j, LIGHTGRAY);

    Console::gotoXY(10, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("^    ^", BLACK);

    Console::gotoXY(11, 11);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" ㅁ  ", BLACK);

    for (int i = 10; i < 16; i++)
        Console::printDot(i, 13, LIGHTRED);

    for (int i = 10; i < 16; i++)
        Console::printDot(i, 14, LIGHTRED);

    for (int i = 9; i < 17; i++)
        Console::printDot(i, 15, LIGHTRED);

    for (int i = 8; i < 18; i++)
        Console::printDot(i, 16, LIGHTRED);

    //말풍선
    for (int i = 5; i > 3; i--)
        Console::printDot(23, i, LIGHTBLUE);

    Console::printDot(22, 6, LIGHTBLUE);
    Console::printDot(21, 7, LIGHTBLUE);
    Console::printDot(22, 8, LIGHTBLUE);

    for (int i = 9; i < 11; i++)
        Console::printDot(23, i, LIGHTBLUE);

    for (int i = 24; i < 47; i++) {
        Console::printDot(i, 4, LIGHTBLUE);
        Console::printDot(i, 10, LIGHTBLUE);
    }
    for (int i = 4; i < 10; i++)
        Console::printDot(46, i, LIGHTBLUE);

    Console::gotoEnd();
}

void Page::workingPage4() {
    frame();

    for (int i = 3; i < WIDTH - 1; i++)
        for (int j = 17; j < HEIGHT; j++)
            Console::printDot(i, j, GRAY);
    for (int i = 52; i < 58; i++)
        Console::printDot(i, 10, LIGHTYELLOW);
    for (int i = 51; i < 59; i++)
        Console::printDot(i, 11, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 12, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        Console::printDot(i, 13, LIGHTYELLOW);
    for (int i = 50; i < 60; i++)
        for (int j = 14; j < 18; j++)
            Console::printDot(i, j, LIGHTYELLOW);
    for (int i = 52; i < 58; i++)
        for (int j = 18; j < 20; j++)
            Console::printDot(i, j, LIGHTMAGENTA);
    Console::printDot(51, 18, LIGHTMAGENTA);
    Console::printDot(50, 19, LIGHTMAGENTA);
    Console::printDot(49, 20, LIGHTGRAY);
    Console::printDot(58, 18, LIGHTMAGENTA);
    Console::printDot(59, 19, LIGHTMAGENTA);
    Console::printDot(60, 20, LIGHTGRAY);
    for (int i = 52; i < 58; i++)
        for (int j = 20; j < 24; j++) {
            Console::printDot(i, j, LIGHTBLUE);
        }
    Console::printDot(52, 24, BLACK);
    Console::printDot(53, 24, BLACK);
    Console::printDot(57, 24, BLACK);
    Console::printDot(56, 24, BLACK);

    //손님
    for (int i = 8; i < 18; i++)
        for (int j = 7; j < 17; j++)
            Console::printDot(i, j, BLACK);

    for (int i = 9; i < 17; i++)
        for (int j = 10; j < 12; j++)
            Console::printDot(i, j, LIGHTGRAY);

    for (int i = 11; i < 15; i++)
        for (int j = 12; j < 14; j++)
            Console::printDot(i, j, LIGHTGRAY);

    Console::gotoXY(10, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("\\    /", BLACK);

    Console::gotoXY(11, 11);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" ㅁ  ", BLACK);

    for (int i = 10; i < 16; i++)
        Console::printDot(i, 13, LIGHTRED);

    for (int i = 10; i < 16; i++)
        Console::printDot(i, 14, LIGHTRED);

    for (int i = 9; i < 17; i++)
        Console::printDot(i, 15, LIGHTRED);

    for (int i = 8; i < 18; i++)
        Console::printDot(i, 16, LIGHTRED);

    //말풍선
    for (int i = 5; i > 3; i--)
        Console::printDot(23, i, LIGHTBLUE);

    Console::printDot(22, 6, LIGHTBLUE);
    Console::printDot(21, 7, LIGHTBLUE);
    Console::printDot(22, 8, LIGHTBLUE);

    for (int i = 9; i < 11; i++)
        Console::printDot(23, i, LIGHTBLUE);

    for (int i = 24; i < 47; i++) {
        Console::printDot(i, 4, LIGHTBLUE);
        Console::printDot(i, 10, LIGHTBLUE);
    }
    for (int i = 4; i < 10; i++)
        Console::printDot(46, i, LIGHTBLUE);

    Console::gotoEnd();
}
