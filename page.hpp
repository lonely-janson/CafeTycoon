#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include "console.hpp"
#include <map>
#include <stdlib.h>
#define WIDTH 65
#define HEIGHT 25

class Page {
  private:
    int num;
    // 현제 페이지 : 0 - 메인화면, 1 - 로그인창
  public:
    void clear();
    void frame();
    void startPage();
    void login();
    // void signUp();
    void mainPage();
    void workingPage1();
    void makingDrink(map<int, int> orderd); // orderd : 주문 정보
    void workingPage2();
    void workingPage3();
    void workingPage4();
};

#endif
