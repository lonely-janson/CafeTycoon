#ifndef __PAGE_HPP__
#define __PAGE_HPP__

#include "console.hpp"
#include <map>
#include <stdlib.h>
#include <vector>
#define WIDTH 65
#define HEIGHT 25

class Page {
  private:
    int num;
    // 현제 페이지 : 0 - 메인화면, 1 - 로그인창
    vector<string> coffeeName = {"아메리카노", "카페라뗴",   "홍차",
                                 "카페모카",   "레몬에이드", "카라멜마끼아또"};
    vector<vector<string>> ingerdients = {
        {"샷 1잔", "샷 2잔", "샷 3잔"},
        {"물", "우유", "탄산수"},
        {"모카시럽", "레몬시럽", "카라멜시럽"},
        {"홍차 티벡", "얼음", "드리즐"}};

    map<int, int>::iterator iter;

  public:
    void clear();
    void frame();
    void startPage();
    void login();
    // void signUp();
    void mainPage();
    void workingPage1(map<int, int> &orderd);
    void makingDrink(map<int, int> &orderd, int level); // orderd : 주문 정보
    void workingPage2();
    void workingPage3();
    void workingPage4();
};

#endif
