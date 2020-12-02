#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include "console.hpp"
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
    void signUp();
    void mainPage();
    void workingPage1_day();
    void makingDrink();
    void workingPage2_day();
    void workingPage3_day();
    void workingPage4_day();
    void workingPage1_night();
    void workingPage2_night();
    void workingPage3_night();
    void workingPage4_night();
    void myInfo();
    void store();
    void showTimer();
    void showRecipe();
    void showRecipeButton();
};

#endif
