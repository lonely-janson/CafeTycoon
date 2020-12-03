#include "console.hpp"
#include "page.hpp"
#include "perform.hpp"

#include <iostream>

using namespace std;

int main() {
    int x;
    int y;
    Page page;
    User user("SON");
    Store store(page);

    // page.startPage();
    // while (1)
    //     if (Console::linux_getch() == ENTER)
    //         break;
    // page.login();

    // while (1)
    //     if (Console::linux_getch() == ENTER)
    //         break;
    page.mainPage();
    char ch;
    x = 11;
    y = 10;
    Console::gotoXY(x, y);
    Console::printColorString(">", RED);
    while (1) { // 방향키 입력
        ch = Console::linux_getch();
        if (ch == ENTER) {
            break;
        } else {
            Console::linux_getch();
            ch = Console::linux_getch();
            if (ch == 'A') {
                // UP
                y = 10;
            } else if (ch == 'B') {
                // DOWN
                y = 23;
            } else if (ch == 'C') {
                // RIGHT
                x = 50;
            } else if (ch == 'D') {
                // LEFT
                x = 11;
            }
            Console::drawCursor(x, y, RED, LIGHTGRAY);
        }
    }

    // page.store();
    // while (1) {
    //     store.printItem(user);
    //     if (store.buyItem(user) == 1)
    //         break;
    // }

    // Game game(page);
    // game.start(user);
    return 0;
}
