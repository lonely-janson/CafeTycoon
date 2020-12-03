#include "console.hpp"
#include "page.hpp"
#include "perform.hpp"

#include <iostream>

using namespace std;

int main() {

    Page page;
    User user("SON");
    Store store(page);

    page.startPage();
    while (1)
        if (Console::linux_getch() == ENTER)
            break;
    page.login();

    while (1)
        if (Console::linux_getch() == ENTER)
            break;
    page.mainPage();

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
