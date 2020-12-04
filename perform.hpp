#ifndef __PERFORM_HPP__
#define __PERFORM_HPP__

#include "page.hpp"
#include "user.hpp"
#include <array>

#define MAX_SIZE sizeof(int) * 5
#define TIME 30

using namespace std;

void gameover(int signum);
void *showTime(void *);

class Game {
  private:
    Page page;

  public:
    static int lastTime;
    Game(Page &_page) { page = _page; }
    void start(User &user);
};

class Store {
  private:
    Page page;
    //레시피 가격
    const int cost[4] = {33000, 55000, 77000, 99000};

    //최소 레벨 조건
    const int level[4] = {2, 3, 4, 5};

  public:
    Store(Page &_page);
    int printItem(User &user);
    int buyItem(User &user); // 1 : 종료
    int isMyItem(int cursor);
};

class Minigame {
  private:
    Page page;
    int gamebleMoney;

  public:
    Minigame(Page &_page);
    int wantGame();
    int startGame(User &user);
    int wantBatting(User &user);
    int sameGame();
    int winGame(User &user);
    int loseGame(User &user);
};

void showMyInfo(Page &page, User &user);

#endif //__PERFORM_HPP__
