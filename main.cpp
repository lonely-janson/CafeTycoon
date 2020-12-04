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
        while (1) {
            page.startPage();
            x = 8;
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
                        switch (x) {
                        case 8:
                            x = 29;
                            break;
                        case 29:
                            x = 51;
                            break;
                        default:
                            break;
                        }

                    } else if (ch == 'D') {
                        // LEFT
                        switch (x) {
                        case 29:
                            x = 8;
                            break;
                        case 51:
                            x = 29;
                            break;
                        default:
                            break;
                        }
                    }
                    Console::drawCursor(x, y, RED, LIGHTMAGENTA);
                }
            }

            if (x == 8) {
                page.login();
                if (data.signIn())
                    break;
            } else if (x == 29) {
                page.signUp();
                data.signUp();
            } else if (x == 51) {
                page.helper1();
                Console::linux_getch();
                page.helper2();
                Console::linux_getch();
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
                } else if (ch == BACK) {
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

            if (ch == BACK) {
                break;
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
                showRanking(page, user);
                break;
            case 73: // myinfo
                showMyInfo(page, user);
                break;
            default:
                break;
            }
        }
    }

    return 0;
}
