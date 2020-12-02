#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include "console.hpp"
#include <stdlib.h>
#define WIDTH 65
#define HEIGHT 25

class Page {
  private:
    int num;
    // 현wo 페이지 : 0 - 메인화면, 1 - 로그인창
  public:
    void clear();
    void frame();
    void startPage();
    void login();
    // void signUp();
    void mainPage();
    void workingPage1();
    void makingDrink();
    void workingPage2();
    void workingPage3();
    void workingPage4();
    void ranking();
    void minigame1(); //고르기
    void minigame2(); //대결
    void minigame3(); //이김
    void minigame4(); //짐
};

#endif
