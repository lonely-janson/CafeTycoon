#include "page.hpp"

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

void Page::workingPage1() {
    frame();

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

    for (int i = 26; i < 52; i++) {
        Console::printDot(i, 6, LIGHTBLUE);
        Console::printDot(i, 14, LIGHTBLUE);
    }
    for (int i = 6; i < 15; i++)
        Console::printDot(52, i, LIGHTBLUE);

    Console::gotoEnd();
}

void Page::makingDrink() {
    frame();

    Console::gotoXY(4, 3);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("총 주문 음료 : ", MAGENTA);
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

    Console::gotoEnd();
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

// ranking 옆에 왕관이 나을지 코인이 나을지 봐주세연,,,
void Page::ranking() {
    frame();

    // R
    for (int i = 5; i < 9; i++) {
        Console::printDot(i, 3, LIGHTRED);
        Console::printDot(i, 5, LIGHTRED);
    }
    Console::printDot(5, 4, LIGHTRED);
    Console::printDot(9, 4, LIGHTRED);

    for (int j = 6; j < 8; j++) {
        Console::printDot(5, j, LIGHTRED);
        Console::printDot(9, j, LIGHTRED);
    }

    // A
    for (int i = 12; i < 15; i++) {
        Console::printDot(i, 3, LIGHTYELLOW);
        Console::printDot(i, 5, LIGHTYELLOW);
    }
    for (int j = 4; j < 8; j++) {
        Console::printDot(11, j, LIGHTYELLOW);
        Console::printDot(15, j, LIGHTYELLOW);
    }

    // N
    for (int j = 3; j < 8; j++) {
        Console::printDot(17, j, LIGHTGREEN);
        Console::printDot(21, j, LIGHTGREEN);
    }
    Console::printDot(18, 4, LIGHTGREEN);
    Console::printDot(19, 5, LIGHTGREEN);
    Console::printDot(20, 6, LIGHTGREEN);

    // K
    for (int j = 3; j < 8; j++)
        Console::printDot(23, j, LIGHTBLUE);

    Console::printDot(24, 5, LIGHTBLUE);
    Console::printDot(25, 5, LIGHTBLUE);
    Console::printDot(26, 4, LIGHTBLUE);
    Console::printDot(26, 6, LIGHTBLUE);
    Console::printDot(27, 3, LIGHTBLUE);
    Console::printDot(27, 7, LIGHTBLUE);

    // I
    for (int i = 29; i < 34; i++) {
        Console::printDot(i, 3, BLUE);
        Console::printDot(i, 7, BLUE);
    }
    for (int j = 4; j < 7; j++)
        Console::printDot(31, j, BLUE);

    // N
    for (int j = 3; j < 8; j++) {
        Console::printDot(35, j, LIGHTMAGENTA);
        Console::printDot(39, j, LIGHTMAGENTA);
    }
    Console::printDot(36, 4, LIGHTMAGENTA);
    Console::printDot(37, 5, LIGHTMAGENTA);
    Console::printDot(38, 6, LIGHTMAGENTA);

    // G
    for (int j = 4; j < 7; j++)
        Console::printDot(41, j, MAGENTA);

    for (int i = 42; i < 46; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }
    for (int j = 5; j < 8; j++)
        Console::printDot(45, j, MAGENTA);

    Console::printDot(44, 5, MAGENTA);

    // crown,,,왕관 같니,,,??어떤지 봐주겟니,,,??
    Console::printDot(48, 7, YELLOW);
    Console::printDot(49, 7, LIGHTCYAN);
    Console::printDot(50, 7, YELLOW);
    Console::printDot(51, 7, LIGHTCYAN);
    Console::printDot(52, 7, YELLOW);
    Console::printDot(53, 7, LIGHTCYAN);
    Console::printDot(54, 7, YELLOW);
    Console::printDot(55, 7, LIGHTCYAN);
    Console::printDot(56, 7, YELLOW);
    Console::printDot(57, 7, LIGHTCYAN);
    Console::printDot(58, 7, YELLOW);

    for (int i = 48; i < 59; i++) {
        Console::printDot(i, 6, LIGHTYELLOW);
    }

    Console::printDot(53, 5, LIGHTRED);
    Console::printDot(48, 5, LIGHTYELLOW);
    Console::printDot(49, 5, LIGHTYELLOW);
    Console::printDot(50, 5, LIGHTYELLOW);
    Console::printDot(51, 5, LIGHTYELLOW);
    Console::printDot(52, 5, LIGHTYELLOW);
    Console::printDot(54, 5, LIGHTYELLOW);
    Console::printDot(55, 5, LIGHTYELLOW);
    Console::printDot(56, 5, LIGHTYELLOW);
    Console::printDot(57, 5, LIGHTYELLOW);
    Console::printDot(58, 5, LIGHTYELLOW);

    Console::printDot(49, 4, LIGHTYELLOW);
    Console::printDot(52, 4, LIGHTYELLOW);
    Console::printDot(53, 4, LIGHTYELLOW);
    Console::printDot(54, 4, LIGHTYELLOW);
    Console::printDot(57, 4, LIGHTYELLOW);

    Console::printDot(53, 3, LIGHTYELLOW);

    // coin,,,왕관이랑 동전이랑 뭐가 낫니,,,?
    /*
    for (int j = 4; j < 7; j++) {
        for (int i = 50; i < 57; i++) {
            Console::printDot(i, j, LIGHTYELLOW);
        }
    }
    for (int i = 51; i < 56; i++) {
        Console::printDot(i, 3, LIGHTYELLOW);
        Console::printDot(i, 7, LIGHTYELLOW);
    }
    Console::printDot(49, 5, LIGHTYELLOW);
    Console::printDot(57, 5, LIGHTYELLOW);
    Console::printDot(53, 4, YELLOW);
    Console::printDot(53, 5, YELLOW);
    Console::printDot(53, 6, YELLOW);
    Console::printDot(56, 3, YELLOW);
    Console::printDot(56, 7, YELLOW);
    Console::printDot(57, 4, YELLOW);
    Console::printDot(58, 5, YELLOW);
    Console::printDot(57, 6, YELLOW);
    */

    // rank box
    for (int i = 5; i < 62; i++) {
        for (int j = 9; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }
    Console::gotoXY(13, 10);
    Console::setBackground(MAGENTA);
    Console::printColorString("RANK", LIGHTGRAY);

    Console::gotoXY(25, 10);
    Console::setBackground(MAGENTA);
    Console::printColorString("NAME", LIGHTGRAY);

    Console::gotoXY(37, 10);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.", LIGHTGRAY);

    Console::gotoXY(49, 10);
    Console::setBackground(MAGENTA);
    Console::printColorString("CUPS", LIGHTGRAY);

    Console::gotoXY(6, 11);
    for (int i = 6; i < 61; i++) {
        Console::setBackground(MAGENTA);
        Console::printColorString("-", LIGHTGRAY);
    }
    Console::gotoXY(6, 12);
    for (int i = 6; i < 61; i++) {
        Console::setBackground(MAGENTA);
        Console::printColorString("-", LIGHTGRAY);
    }

    // rank 1st
    Console::gotoXY(13, 14);
    Console::setBackground(MAGENTA);
    Console::printColorString("1ST", LIGHTRED);

    Console::gotoXY(25, 14);
    Console::setBackground(MAGENTA);
    Console::printColorString("꾸꾸", LIGHTRED);

    Console::gotoXY(37, 14);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.6", LIGHTRED);

    Console::gotoXY(49, 14);
    Console::setBackground(MAGENTA);
    Console::printColorString("100", LIGHTRED);

    // rank 2nd
    Console::gotoXY(13, 16);
    Console::setBackground(MAGENTA);
    Console::printColorString("2ND", LIGHTYELLOW);

    Console::gotoXY(25, 16);
    Console::setBackground(MAGENTA);
    Console::printColorString("끼끼", LIGHTYELLOW);

    Console::gotoXY(37, 16);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.5", LIGHTYELLOW);

    Console::gotoXY(49, 16);
    Console::setBackground(MAGENTA);
    Console::printColorString("89", LIGHTYELLOW);

    // rank 3rd
    Console::gotoXY(13, 18);
    Console::setBackground(MAGENTA);
    Console::printColorString("3RD", LIGHTGREEN);

    Console::gotoXY(25, 18);
    Console::setBackground(MAGENTA);
    Console::printColorString("까까", LIGHTGREEN);

    Console::gotoXY(37, 18);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.4", LIGHTGREEN);

    Console::gotoXY(49, 18);
    Console::setBackground(MAGENTA);
    Console::printColorString("70", LIGHTGREEN);

    // rank 4th
    Console::gotoXY(13, 20);
    Console::setBackground(MAGENTA);
    Console::printColorString("4th", LIGHTGRAY);

    Console::gotoXY(25, 20);
    Console::setBackground(MAGENTA);
    Console::printColorString("꼬꼬", LIGHTGRAY);

    Console::gotoXY(37, 20);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.3", LIGHTGRAY);

    Console::gotoXY(49, 20);
    Console::setBackground(MAGENTA);
    Console::printColorString("50", LIGHTGRAY);

    // rank 5th
    Console::gotoXY(13, 22);
    Console::setBackground(MAGENTA);
    Console::printColorString("5th", LIGHTGRAY);

    Console::gotoXY(25, 22);
    Console::setBackground(MAGENTA);
    Console::printColorString("뀨뀨", LIGHTGRAY);

    Console::gotoXY(37, 22);
    Console::setBackground(MAGENTA);
    Console::printColorString("LV.3", LIGHTGRAY);

    Console::gotoXY(49, 22);
    Console::setBackground(MAGENTA);
    Console::printColorString("40", LIGHTGRAY);

    Console::gotoEnd();
}

//묵찌빠 선택
void Page::minigame1() {
    frame();

    // M
    for (int j = 3; j < 8; j++) {
        Console::printDot(5, j, LIGHTMAGENTA);
        Console::printDot(9, j, LIGHTMAGENTA);
    }
    Console::printDot(6, 4, LIGHTMAGENTA);
    Console::printDot(7, 5, LIGHTMAGENTA);
    Console::printDot(8, 4, LIGHTMAGENTA);

    // I
    for (int i = 11; i < 16; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }
    for (int j = 4; j < 7; j++)
        Console::printDot(13, j, MAGENTA);

    // N
    for (int j = 3; j < 8; j++) {
        Console::printDot(17, j, LIGHTMAGENTA);
        Console::printDot(21, j, LIGHTMAGENTA);
    }
    Console::printDot(18, 4, LIGHTMAGENTA);
    Console::printDot(19, 5, LIGHTMAGENTA);
    Console::printDot(20, 6, LIGHTMAGENTA);

    // I
    for (int i = 23; i < 28; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }
    for (int j = 4; j < 7; j++)
        Console::printDot(25, j, MAGENTA);

    // G
    for (int j = 4; j < 7; j++)
        Console::printDot(39, j, LIGHTMAGENTA);

    for (int i = 40; i < 44; i++) {
        Console::printDot(i, 3, LIGHTMAGENTA);
        Console::printDot(i, 7, LIGHTMAGENTA);
    }
    for (int j = 5; j < 8; j++)
        Console::printDot(43, j, LIGHTMAGENTA);

    Console::printDot(42, 5, LIGHTMAGENTA);

    // A
    for (int i = 46; i < 49; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 5, MAGENTA);
    }
    for (int j = 4; j < 8; j++) {
        Console::printDot(45, j, MAGENTA);
        Console::printDot(49, j, MAGENTA);
    }

    // M
    for (int j = 3; j < 8; j++) {
        Console::printDot(51, j, LIGHTMAGENTA);
        Console::printDot(55, j, LIGHTMAGENTA);
    }
    Console::printDot(52, 4, LIGHTMAGENTA);
    Console::printDot(53, 5, LIGHTMAGENTA);
    Console::printDot(54, 4, LIGHTMAGENTA);

    // E
    for (int j = 3; j < 8; j++)
        Console::printDot(57, j, MAGENTA);

    for (int i = 58; i < 62; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 5, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }

    // character
    for (int i = 31; i < 36; i++) {
        for (int j = 3; j < 7; j++) {
            Console::printDot(i, j, RED);
        }
    }
    for (int j = 4; j < 8; j++) {
        Console::printDot(30, j, RED);
        Console::printDot(36, j, RED);
    }
    Console::printDot(32, 7, RED);
    Console::printDot(34, 7, RED);
    Console::gotoXY(32, 4);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("*", BLACK);
    Console::gotoXY(34, 4);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("*", BLACK);

    // select
    Console::gotoXY(23, 9);
    Console::setBackground(MAGENTA);
    Console::printColorString(" ▶ 당신의 선택은!? ◀  ", LIGHTGRAY);

    Console::gotoEnd();
}

// pc대결 화면
void Page::minigame2() {
    frame();

    // player
    for (int i = 3; i < 33; i++) {
        for (int j = 3; j < 13; j++) {
            Console::printDot(i, j, LIGHTRED);
        }
    }
    for (int j = 4; j < 13; j++)
        Console::printDot(33, j, LIGHTRED);
    for (int j = 5; j < 13; j++)
        Console::printDot(34, j, LIGHTRED);
    for (int j = 6; j < 13; j++)
        Console::printDot(35, j, LIGHTRED);
    for (int j = 7; j < 13; j++)
        Console::printDot(36, j, LIGHTRED);
    for (int j = 8; j < 13; j++)
        Console::printDot(37, j, LIGHTRED);
    for (int j = 9; j < 13; j++)
        Console::printDot(38, j, LIGHTRED);
    for (int j = 10; j < 13; j++)
        Console::printDot(39, j, LIGHTRED);
    Console::printDot(40, 11, LIGHTRED);
    Console::printDot(40, 12, LIGHTRED);
    Console::printDot(41, 12, LIGHTRED);

    //주먹

    //가위

    //보

    // pc
    for (int i = 34; i < 64; i++) {
        for (int j = 14; j < 24; j++) {
            Console::printDot(i, j, BLUE);
        }
    }
    for (int j = 15; j < 24; j++)
        Console::printDot(33, j, BLUE);
    for (int j = 16; j < 24; j++)
        Console::printDot(32, j, BLUE);
    for (int j = 17; j < 24; j++)
        Console::printDot(31, j, BLUE);
    for (int j = 18; j < 24; j++)
        Console::printDot(30, j, BLUE);
    for (int j = 19; j < 24; j++)
        Console::printDot(29, j, BLUE);
    for (int j = 20; j < 24; j++)
        Console::printDot(28, j, BLUE);
    for (int j = 21; j < 24; j++)
        Console::printDot(27, j, BLUE);
    Console::printDot(26, 22, BLUE);
    Console::printDot(26, 23, BLUE);
    Console::printDot(25, 23, BLUE);

    //주먹

    //가위

    //보

    // vs
    for (int j = 9; j < 12; j++) {
        Console::printDot(25, j, LIGHTYELLOW);
        Console::printDot(31, j, LIGHTYELLOW);
    }
    Console::printDot(26, 9, YELLOW);
    Console::printDot(26, 10, YELLOW);
    Console::printDot(27, 11, YELLOW);
    Console::printDot(27, 12, YELLOW);
    Console::printDot(28, 13, YELLOW);
    for (int j = 11; j < 14; j++) {
        Console::printDot(26, j, LIGHTYELLOW);
        Console::printDot(30, j, LIGHTYELLOW);
    }
    Console::printDot(32, 9, YELLOW);
    Console::printDot(32, 10, YELLOW);
    Console::printDot(32, 11, YELLOW);
    Console::printDot(31, 12, YELLOW);
    Console::printDot(31, 13, YELLOW);
    Console::printDot(30, 14, YELLOW);
    Console::printDot(29, 15, YELLOW);
    for (int j = 13; j < 15; j++) {
        Console::printDot(27, j, LIGHTYELLOW);
        Console::printDot(29, j, LIGHTYELLOW);
    }
    Console::printDot(28, 14, LIGHTYELLOW);
    Console::printDot(28, 15, LIGHTYELLOW);

    for (int i = 35; i < 40; i++) {
        Console::printDot(i, 9, LIGHTYELLOW);
        Console::printDot(i, 12, LIGHTYELLOW);
        Console::printDot(i, 15, LIGHTYELLOW);
    }
    Console::printDot(34, 10, LIGHTYELLOW);
    Console::printDot(34, 11, LIGHTYELLOW);
    Console::printDot(40, 10, LIGHTYELLOW);
    Console::printDot(40, 13, LIGHTYELLOW);
    Console::printDot(40, 14, LIGHTYELLOW);
    Console::printDot(34, 14, LIGHTYELLOW);
    Console::printDot(35, 10, YELLOW);
    Console::printDot(35, 11, YELLOW);
    Console::printDot(40, 9, YELLOW);
    Console::printDot(41, 10, YELLOW);
    Console::printDot(40, 12, YELLOW);
    Console::printDot(41, 13, YELLOW);
    Console::printDot(41, 14, YELLOW);
    Console::printDot(40, 15, YELLOW);
    Console::printDot(35, 14, YELLOW);

    Console::gotoEnd();
}

//결과화면 - 이김
void Page::minigame3() {
    frame();

    // Y
    for (int j = 5; j < 8; j++)
        Console::printDot(7, j, LIGHTMAGENTA);
    Console::printDot(6, 4, LIGHTMAGENTA);
    Console::printDot(8, 4, LIGHTMAGENTA);
    Console::printDot(5, 3, LIGHTMAGENTA);
    Console::printDot(9, 3, LIGHTMAGENTA);

    // O
    for (int i = 12; i < 15; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }
    for (int j = 4; j < 7; j++) {
        Console::printDot(11, j, MAGENTA);
        Console::printDot(15, j, MAGENTA);
    }

    // U
    for (int i = 18; i < 21; i++)
        Console::printDot(i, 7, LIGHTMAGENTA);
    for (int j = 3; j < 7; j++) {
        Console::printDot(17, j, LIGHTMAGENTA);
        Console::printDot(21, j, LIGHTMAGENTA);
    }

    // W
    for (int j = 3; j < 8; j++) {
        Console::printDot(45, j, LIGHTRED);
        Console::printDot(49, j, LIGHTRED);
    }
    Console::printDot(46, 6, LIGHTRED);
    Console::printDot(47, 5, LIGHTRED);
    Console::printDot(48, 6, LIGHTRED);

    // I
    for (int i = 51; i < 56; i++) {
        Console::printDot(i, 3, LIGHTRED);
        Console::printDot(i, 7, LIGHTRED);
    }
    for (int j = 4; j < 7; j++)
        Console::printDot(53, j, LIGHTRED);

    // N
    for (int j = 3; j < 8; j++) {
        Console::printDot(57, j, LIGHTRED);
        Console::printDot(61, j, LIGHTRED);
    }
    Console::printDot(58, 4, LIGHTRED);
    Console::printDot(59, 5, LIGHTRED);
    Console::printDot(60, 6, LIGHTRED);

    // result box
    for (int i = 5; i < 62; i++) {
        for (int j = 9; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }
    Console::gotoXY(20, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("당신은 대결에서 이겼습니다.", LIGHTGRAY);
    Console::gotoXY(19, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("그에 따라 보상을 받게 됩니다.", LIGHTGRAY);

    // reward box
    for (int i = 18; i < 49; i++) {
        Console::printDot(i, 15, LIGHTRED);
        for (int j = 16; j < 22; j++) {
            Console::printDot(i, j, LIGHTGRAY);
        }
    }
    Console::gotoXY(30, 15);
    Console::setBackground(LIGHTRED);
    Console::printColorString("REWARD", LIGHTGRAY);
    Console::gotoXY(29, 18);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("보상내용", LIGHTRED);

    Console::gotoEnd();
}

//결과화면 - 짐
void Page::minigame4() {
    frame();

    // Y
    for (int j = 5; j < 8; j++)
        Console::printDot(7, j, LIGHTMAGENTA);
    Console::printDot(6, 4, LIGHTMAGENTA);
    Console::printDot(8, 4, LIGHTMAGENTA);
    Console::printDot(5, 3, LIGHTMAGENTA);
    Console::printDot(9, 3, LIGHTMAGENTA);

    // O
    for (int i = 12; i < 15; i++) {
        Console::printDot(i, 3, MAGENTA);
        Console::printDot(i, 7, MAGENTA);
    }
    for (int j = 4; j < 7; j++) {
        Console::printDot(11, j, MAGENTA);
        Console::printDot(15, j, MAGENTA);
    }

    // U
    for (int i = 18; i < 21; i++)
        Console::printDot(i, 7, LIGHTMAGENTA);
    for (int j = 3; j < 7; j++) {
        Console::printDot(17, j, LIGHTMAGENTA);
        Console::printDot(21, j, LIGHTMAGENTA);
    }

    // L
    for (int j = 3; j < 8; j++)
        Console::printDot(39, j, BLUE);
    for (int i = 40; i < 44; i++)
        Console::printDot(i, 7, BLUE);

    // O
    for (int i = 46; i < 49; i++) {
        Console::printDot(i, 3, BLUE);
        Console::printDot(i, 7, BLUE);
    }
    for (int j = 4; j < 7; j++) {
        Console::printDot(45, j, BLUE);
        Console::printDot(49, j, BLUE);
    }

    // S
    for (int i = 51; i < 56; i++) {
        Console::printDot(i, 3, BLUE);
        Console::printDot(i, 5, BLUE);
        Console::printDot(i, 7, BLUE);
    }
    Console::printDot(51, 4, BLUE);
    Console::printDot(55, 6, BLUE);

    // E
    for (int j = 3; j < 8; j++)
        Console::printDot(57, j, BLUE);

    for (int i = 58; i < 62; i++) {
        Console::printDot(i, 3, BLUE);
        Console::printDot(i, 5, BLUE);
        Console::printDot(i, 7, BLUE);
    }

    // result box
    for (int i = 5; i < 62; i++) {
        for (int j = 9; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }
    Console::gotoXY(21, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("당신은 대결에서 졌습니다.", LIGHTGRAY);
    Console::gotoXY(18, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("그에 따라 패널티를 받게 됩니다.", LIGHTGRAY);

    // penalty box
    for (int i = 18; i < 49; i++) {
        Console::printDot(i, 15, BLUE);
        for (int j = 16; j < 22; j++) {
            Console::printDot(i, j, LIGHTGRAY);
        }
    }
    Console::gotoXY(30, 15);
    Console::setBackground(BLUE);
    Console::printColorString("PENALTY", LIGHTGRAY);
    Console::gotoXY(29, 18);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("패널티내용", BLUE);

    Console::gotoEnd();
}

void Page::finish() {
    frame();

    // T
    for (int i = 5; i < 10; i++)
        Console::printDot(i, 3, LIGHTBLUE);
    for (int j = 4; j < 8; j++)
        Console::printDot(7, j, LIGHTBLUE);

    // O
    for (int i = 12; i < 15; i++) {
        Console::printDot(i, 3, LIGHTBLUE);
        Console::printDot(i, 7, LIGHTBLUE);
    }
    for (int j = 4; j < 7; j++) {
        Console::printDot(11, j, LIGHTBLUE);
        Console::printDot(15, j, LIGHTBLUE);
    }

    // D
    for (int i = 17; i < 21; i++) {
        Console::printDot(i, 3, LIGHTBLUE);
        Console::printDot(i, 7, LIGHTBLUE);
    }
    for (int j = 4; j < 7; j++)
        Console::printDot(17, j, LIGHTBLUE);
    for (int j = 4; j < 7; j++)
        Console::printDot(21, j, LIGHTBLUE);

    // A
    for (int i = 24; i < 27; i++) {
        Console::printDot(i, 3, LIGHTBLUE);
        Console::printDot(i, 5, LIGHTBLUE);
    }
    for (int j = 4; j < 8; j++) {
        Console::printDot(23, j, LIGHTBLUE);
        Console::printDot(27, j, LIGHTBLUE);
    }

    // Y
    for (int j = 5; j < 8; j++)
        Console::printDot(31, j, LIGHTBLUE);
    Console::printDot(30, 4, LIGHTBLUE);
    Console::printDot(32, 4, LIGHTBLUE);
    Console::printDot(29, 3, LIGHTBLUE);
    Console::printDot(33, 3, LIGHTBLUE);

    // today box
    for (int i = 5; i < 62; i++) {
        for (int j = 9; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }
    //목록
    Console::gotoXY(8, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("판매량", LIGHTRED);
    Console::gotoXY(8, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("실패한 잔 수", LIGHTYELLOW);
    Console::gotoXY(8, 15);
    Console::setBackground(MAGENTA);
    Console::printColorString("누적 판매량", LIGHTGREEN);
    Console::gotoXY(8, 17);
    Console::setBackground(MAGENTA);
    Console::printColorString("오늘의 수익", LIGHTBLUE);
    Console::gotoXY(8, 19);
    Console::setBackground(MAGENTA);
    Console::printColorString("총 수익", LIGHTMAGENTA);
    Console::gotoXY(35, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("현재 레벨", LIGHTCYAN);
    Console::gotoXY(35, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("다음 레벨까지", LIGHTGRAY);
    //값
    Console::gotoXY(24, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("15잔", LIGHTGRAY);
    Console::gotoXY(24, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("1잔", LIGHTGRAY);
    Console::gotoXY(24, 15);
    Console::setBackground(MAGENTA);
    Console::printColorString("60잔", LIGHTGRAY);
    Console::gotoXY(24, 17);
    Console::setBackground(MAGENTA);
    Console::printColorString("한석원", LIGHTGRAY);
    Console::gotoXY(24, 19);
    Console::setBackground(MAGENTA);
    Console::printColorString("이태원", LIGHTGRAY);
    Console::gotoXY(52, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("4", LIGHTGRAY);
    Console::gotoXY(52, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("10%", LIGHTGRAY);

    // COFFEE
    for (int i = 47; i < 54; i++) {
        Console::printDot(i, 16, LIGHTGRAY);
        Console::printDot(i, 17, BLACK);
        for (int j = 18; j < 23; j++) {
            Console::printDot(i, j, LIGHTGRAY);
        }
    }
    for (int j = 17; j < 22; j++) {
        Console::printDot(46, j, LIGHTGRAY);
        Console::printDot(54, j, LIGHTGRAY);
    }
    for (int i = 55; i < 58; i++) {
        Console::printDot(i, 18, LIGHTGRAY);
        Console::printDot(i, 20, LIGHTGRAY);
    }
    Console::printDot(57, 19, LIGHTGRAY);
    Console::printDot(46, 16, LIGHTGRAY);
    Console::printDot(54, 16, LIGHTGRAY);

    Console::gotoXY(33, 22);
    Console::setBackground(MAGENTA);
    Console::printColorString("Cafe Tycoon", LIGHTGRAY);

    Console::gotoEnd();
}
