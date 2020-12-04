#include "console.hpp"
#include "page.hpp"
#include "perform.hpp"

#include <iostream>

using namespace std;

int main() {
    int x;
    int y;
    char ch;
    Page page;
    Store store(page);
    Minigame minigame(page);
    Game game(page);
    Data data;
    // User user("SON");

    while (1) {
        page.startPage();
        x = 13;
        y = 22;
        Console::gotoXY(x, y);
        Console::printColorString(">", RED);
        while (1) { // 방향키 입력
            ch = Console::linux_getch();
            if (ch == ENTER) {
                break;
            } else {
                Console::linux_getch();
                ch = Console::linux_getch();
                if (ch == 'C') {
                    // RIGHT
                    x = 45;
                } else if (ch == 'D') {
                    // LEFT
                    x = 13;
                }
                Console::drawCursor(x, y, RED, LIGHTMAGENTA);
            }
        }

        if (x == 13) {
            page.login();
            if (data.signIn())
                break;
        } else {
            page.signUp();
            data.signUp();
        }
    }

    User user(data);

    while (1) {
        page.mainPage();
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
                    switch (y) {
                    case 13:
                        y = 10;
                        x = 11;
                        break;
                    case 23:
                        y = 13;
                        x = 22;
                    default:
                        break;
                    }
                } else if (ch == 'B') {
                    // DOWN
                    switch (y) {
                    case 10:
                        y = 13;
                        x = 22;
                        break;
                    case 13:
                        y = 23;
                        x = 11;
                    default:
                        break;
                    }
                } else if (ch == 'D') {
                    // LEFT
                    if (y != 13)
                        x = 11;
                } else if (ch == 'C') {
                    // RIGHT
                    if (y != 13)
                        x = 50;
                }
                Console::drawCursor(x, y, RED, LIGHTGRAY);
            }
        }

        switch (x + y) {
        case 21: // miniGame
            if (minigame.wantGame() == 1) {
                int gambleMoney = minigame.wantBatting(user);
                if (gambleMoney > 0) {
                    minigame.startGame(user);
                }
            }
            break;
        case 60: // store
            page.store();
            while (1) {
                store.printItem(user);
                if (store.buyItem(user) == 1)
                    break;
            }
            break;
        case 35: // game
            page.clear();
            game.start(user);
            break;
        case 34: // ranking
            page.ranking();
            Console::linux_getch();
            break;
        case 73: // myinfo
            showMyInfo(page, user);
            break;
        default:
            break;
        }
    }
    return 0;
}
