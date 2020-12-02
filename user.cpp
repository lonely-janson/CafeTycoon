#include "user.hpp"

User::User(string _name) {
    name = _name;
    level = 10; // "?? ??"
    money = 0;
    countSell = 0;
    recipe.assign(2, true);
    maxEx = 100;
    curEx = 1;
}

User::User(User &user) {
    name = user.name;
    level = user.level;
    money = user.money;
    countSell = user.countSell;
    recipe.clear();
    recipe.assign(user.recipe.begin(), user.recipe.end());
    maxEx = user.maxEx;
    curEx = user.curEx;
}

int User::addEx(int ex) {
    curEx += ex;

    if (curEx >= maxEx) {
        level++;
        curEx -= maxEx;
        maxEx *= 2;
        return 1;
    }

    return 0;
}
