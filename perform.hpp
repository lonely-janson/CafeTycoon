#ifndef __PERFORM_HPP__
#define __PERFORM_HPP__

#include "user.hpp"

#include "page.hpp"
#include <string>
#include <vector>

using namespace std;

class Data {
  private:
    string username;
    string dataPath;

  public:
    Data();
    bool signUp(); //회원가입
    bool signIn(); //로그인
};

void gameover(int signum);
void *showTime(void *);

struct __MSG {
    long type;
    int data[3]; // 0 : 돈 , 1 : 판매잔수, 2 : 경험치
};
typedef struct __MSG Msg;

class Game {
  private:
    /*
      RECIPE {
          americano = 12,
          cafeLattee = 32,
          blackTea = 1010,
          cafeMocha = 132,
          lemonade = 3350,
          caramelMacchiato = 5533
      };

      INGERDIENTS {
          shot1 = 1,
          shot2 = 2,
          shot3 = 3,
          water = 10,
          milk = 30,
          sparklingWater = 50,
          mochaSyrup = 100,
          lemonSyrup = 300,
          caramelSyrup = 500,
          blackTeaBag = 1000,
          ice = 3s000,
          caramelDrizzle = 5000
      };*/

    Page page;

  public:
    Game() { page = Page(); }
    void start(User &user);
};

class Store {
  private:
    int level; //사용자 레벨 - 생성자 초기화 만들기
    int money; //사용자 소유금액 - 생성자 초기화 만들기

    //구매여부 확인
    int menu1, menu2, menu3, menu4;

    //경로
    char *path_menu1; //= "/home/id(???)/recipes/menu1"; //경로 수정해야함!!
    char *path_menu2; //= "/home/id(???)/recipes/menu2";
    char *path_menu3; //= "/home/id(???)/0recipes/menu3";
    char *path_menu4; //= "/home/id(???)/recipes/menu4";

    //레시피 가격
    int cost_menu1 = 1;
    int cost_menu2 = 2;
    int cost_menu3 = 3;
    int cost_menu4 = 4;

    //최소 레벨 조건
    int lev_menu1 = 2;
    int lev_menu2 = 3;
    int lev_menu3 = 4;
    int lev_menu4 = 5;

  public:
    Store();
    int printItem(int level);
    int buyItem(int cursor);
    int isMyItem(int cursor);
};

#endif //__PERFORM_HPP__
