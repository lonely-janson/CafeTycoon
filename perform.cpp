#include "perform.hpp"
#include "console.hpp"
#include "user.hpp"
#include <cstring>
#include <dirent.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <pthread.h>
#include <queue>
#include <random>
#include <signal.h>
#include <stack>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

void gameOver(int signum) {
    int status;
    //게임종료 창 보여주기
    cout << "gameOver\n";
    exit(0);
}

int Game::lastTime = TIME;

void *showTime(void *) {
    for (int i = 0; i < TIME; i++) {
        sleep(1);
        Game::lastTime--;
    }
}

void Game::start(User &user) {
    int pid; // 첫 번쨰 pid
    key_t key;
    int id;
    int *shmaddr = NULL; // 0:금액, 1:잔수, 2:경험치 3:실패, 4:성공
    lastTime = TIME;

    string checkShowRecipe;

    key = ftok("./main.cpp", 1);
    id = shmget(key, MAX_SIZE, IPC_CREAT | 0600);

    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
        return;
    } else if (pid == 0) {
        // 데이터 통신
        shmaddr = (int *)shmat(id, NULL, 0);
        memset(shmaddr, 0, sizeof(shmaddr));
        //게임 진행
        map<int, int> orderd; // 커피 종류 및 수량 저장
        int numberOfType;     // 커피 종류 개수
        int kind;             // 커피 종류
        int showSelectY = 10;
        int color;
        int x;
        int y;

        vector<string> coffeeName = {"아메리카노", "카페라뗴",
                                     "홍차",       "카페모카",
                                     "레몬에이드", "카라멜마끼아또"};
        const vector<int> ex = {10, 10, 12, 15, 17, 20};
        const vector<int> coffeePrice = {2500, 3000, 3500, 4000, 4500, 5000};
        const vector<int> recipe = {12, 32, 1010, 132, 3350, 5532};
        // 올바른 recipe 값
        // americano = 12,cafeLattee = 22, blackTea = 1010, cafeMocha = 122,
        // lemonade = 2250,caramelMacchiato = 5522
        const vector<vector<string>> ingerdients = {
            {"샷 1잔", "샷 2잔", "샷 3잔"},
            {"물", "우유", "탄산수"},
            {"모카시럽", "레몬시럽", "카라멜시럽"},
            {"홍차 티벡", "얼음", "드리즐"}};

        map<int, string> inger = {
            {1, "샷 1잔"},      {2, "샷2잔"},      {3, "샷3잔"},
            {10, "물"},         {30, "우유"},      {50, "탄산수"},
            {100, "모카시럽"},  {300, "레몬시럽"}, {500, "카라멜시럽"},
            {1000, "홍차티백"}, {3000, "얼음"},    {5000, "드리즐"}};

        const double failPercnt = 0.8;

        map<int, int>::iterator iter;

        int selectIngerdients; //선택한 커피 재료 모음
        int select;            // 선택한 재료 저장
        int level = (user.getlevel() > 5) ? 5 : user.getlevel();

        vector<vector<int>> makeCoffee(
            6, vector<int>(5)); // 최종 제작 커피 저장 배열
        bool successOrfail;     // 성공 여부
        int totalPrice;         // 획득한 돈
        int totalCup;           // 판매잔 수
        int totalEx;            // 총 획득 경험치
        int tempPrice;          // 공유 메모리에 저장할 데이터
        int tempSell;           // 공유 메모리에 저장할 금액
        int tempEx;             // 공유 메모리에 저장할 경험치
        int failCount = 0;
        int succesCount = 0;
        int typeNum = 2;

        char ch; // 키보드 입력

        //난수 생성
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> randNumberOfType(1, typeNum); // 종류 개수
        uniform_int_distribution<int> randQuantity(1, 5);       // 주문 개수
        uniform_int_distribution<int> randKindOfType(0, level); //커피 종류

        //타이머 설정
        alarm(TIME);

        // 시간 보여주기
        pthread_t tid = 0;
        if (pthread_create(&tid, NULL, showTime, NULL)) {
            perror("pthread_creat() error!");
            exit(-1);
        }
        pthread_detach(tid);

        if (signal(SIGALRM, gameOver) == SIG_ERR) {
            perror("signal() error!");
        }

        while (1) {
            orderd.clear();
            totalCup = 0;

            numberOfType = randNumberOfType(gen);

            // 메뉴 주문
            for (int i = 0; i < numberOfType;) {

                kind = randKindOfType(gen);

                if (user.getRecipe(kind) && orderd[kind] == 0) {
                    orderd[kind] = randQuantity(gen);
                    totalCup += orderd[kind];
                    i++;
                }
            }

            color = LIGHTGRAY;
            //주문 정보 출력
            if (lastTime > lastTime / 2) {
                page.workingPage1_day(orderd);
            } else {
                page.workingPage1_night(orderd);
            }

            //레시피 출력 여부
            page.showRecipeButton();
            x = 20;
            y = HEIGHT - 1;
            Console::gotoXY(x, y);
            Console::setBackground(LIGHTYELLOW);
            Console::printColorString(">", RED);
            while (1) { // 방향키 입력
                ch = Console::linux_getch();
                if (ch == ENTER) {
                    if (x == 20)
                        checkShowRecipe = "y";
                    else
                        checkShowRecipe = "n";
                    break;
                } else {
                    Console::linux_getch();
                    ch = Console::linux_getch();
                    if (ch == 'C') {
                        // RIGHT
                        x = 26;
                    } else if (ch == 'D') {
                        // LEFT
                        x = 20;
                    }
                    Console::drawCursor(x, y, RED, LIGHTYELLOW);
                }
            }

            if (checkShowRecipe == "y") {
                // ------ 디자인 변경 필요 -----
                int tempY = 8;
                page.showRecipe();

                //레시피 출력
                for (iter = orderd.begin(); iter != orderd.end(); iter++) {
                    Console::gotoXY(7, tempY);
                    tempY += 2;
                    switch (iter->first) {
                    case 0:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString("아메리카노 : 샷2잔, 물\n",
                                                  MAGENTA);
                        break;
                    case 1:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString("카페라뗴 : 샷2잔, 우유\n",
                                                  MAGENTA);
                        break;
                    case 2:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString("홍차 : 홍차티벡, 물\n",
                                                  MAGENTA);
                        break;
                    case 3:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString(
                            "카페모카 : 샷2잔, 물, 모카시럽\n", MAGENTA);
                        break;
                    case 4:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString(
                            "레몬에이드 : 탄산수, 레몬시럽, 얼음\n", MAGENTA);
                        break;
                    case 5:
                        Console::setBackground(LIGHTGRAY);
                        Console::printColorString(
                            "카라멜마키야또 : 샷2잔, 우유, 카라멜 시럽, 카라멜 "
                            "드리즐\n",
                            MAGENTA);
                        break;
                    }
                }

                Console::gotoXY(53, HEIGHT - 2);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString(">", RED);
                while (Console::linux_getch() != ENTER)
                    ;
            }

            page.makingDrink(orderd, user);

            //배열 초기화

            x = 4;
            y = 12;
            int drinkingCount = 0;
            int syrupLevel = (level > 4) ? 4 : level;
            select = 1;

            iter = orderd.begin();
            for (int i = 0; iter != orderd.end(); iter++, i++) {
                for (int j = 0; j < iter->second; j++) {
                    Console::gotoXY(26, 5);
                    Console::setBackground(color);
                    Console::printColorString(coffeeName[iter->first].c_str(),
                                              MAGENTA);

                    string drinkCountStr = "(" + to_string(drinkingCount);
                    drinkCountStr += '/';
                    drinkCountStr += to_string(totalCup) + ")";
                    drinkingCount++;
                    Console::gotoXY(58, 4);
                    Console::setBackground(color);
                    Console::printColorString("      ", MAGENTA);
                    Console::gotoXY(58, 4);
                    Console::setBackground(color);
                    Console::printColorString(drinkCountStr.c_str(), MAGENTA);

                    Console::gotoXY(5, 12);

                    selectIngerdients = 0;

                    while (1) { // 커피 재료 선택
                        // 키보드 입력
                        while (1) { // 방향키 입력
                            ch = Console::linux_getch();
                            if (ch == SPACE) {
                                ch = 'y';
                                break;
                            } else if (ch == ENTER) {
                                break;
                            } else {
                                Console::linux_getch();
                                ch = Console::linux_getch();
                                if (ch == 'A') {
                                    // UP
                                    if (y > 12) {
                                        //재료 라인
                                        y -= 2;
                                        if (x == 4)
                                            select -= 1;
                                        if (x == 14)
                                            select -= 20;
                                        if (x == 25)
                                            select -= 200;
                                        if (x == 36)
                                            select -= 2000;
                                        Console::drawCursor(x, y, RED, color);
                                    }
                                } else if (ch == 'B') {
                                    // DOWN
                                    if (x == 4 && y < 16) {
                                        //재료 라인
                                        y += 2;
                                        select += 1;
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 14 &&
                                               y < 14 + (level / 3) * 2) {
                                        // 베이스 라인
                                        y += 2;
                                        select += 20;
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 25 &&
                                               y < 12 + (syrupLevel - 2) * 2) {
                                        // 시럽 라인
                                        y += 2;
                                        select += 200;
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 36 &&
                                               y < 12 + (level - 3) * 2) {
                                        // 재료 라인
                                        y += 2;
                                        select += 2000;
                                        Console::drawCursor(x, y, RED, color);
                                    }
                                } else if (ch == 'C') { // RIGHT
                                    if (x == 4) {
                                        //샷 라인
                                        x = 14;
                                        switch (select) {
                                        case 1:
                                            select = 10;
                                            break;
                                        case 2:
                                            select = 30;
                                            break;
                                        case 3:
                                            select = 50;
                                            break;
                                        default:
                                            break;
                                        }

                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 14) {
                                        //베이스 라인
                                        x = 25;
                                        select *= 10;
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 25) {
                                        //시럽 라인
                                        x = 36;
                                        select *= 10;
                                        Console::drawCursor(x, y, RED, color);
                                    }
                                } else if (ch == 'D') { // LEFT
                                    if (x == 14) {
                                        //샷 라인
                                        x = 4;
                                        switch (select) {
                                        case 10:
                                            select = 1;
                                            break;
                                        case 30:
                                            select = 2;
                                            break;
                                        case 50:
                                            select = 3;
                                            break;
                                        default:
                                            break;
                                        }
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 25) {
                                        //베이스 라인
                                        x = 14;
                                        select /= 10;
                                        Console::drawCursor(x, y, RED, color);
                                    } else if (x == 36) {
                                        //시럽 라인
                                        x = 25;
                                        select /= 10;
                                        Console::drawCursor(x, y, RED, color);
                                    }
                                }
                            }
                        }

                        if (ch == 'y') {
                            //좌표 초기화
                            x = 4;
                            y = 12;
                            //커서 지우기
                            Console::drawCursor(x, y, RED, color);

                            // 선택된 재료 글씨 지우기
                            for (int i = 10; i < showSelectY; i++) {
                                Console::gotoXY(50, i);
                                Console::setBackground(color);
                                Console::printColorString("            ");
                            }

                            // 현제 재조 중인 글씨 지우기
                            Console::gotoXY(26, 5);
                            Console::setBackground(color);
                            Console::printColorString("             ");
                            //선택된 재료 초기화
                            showSelectY = 10;
                            select = 1;

                            //커피만들기
                            makeCoffee[i][j] = selectIngerdients;
                            break;
                        }

                        // 같은 종류 재료 중복 추가 불가!
                        if (select % 10 != 0) {
                            //샷 라인
                            if (selectIngerdients % 10 == 0) {
                                selectIngerdients += select;
                                Console::setBackground(color);
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(x, y);
                                Console::drawCursor(x, y, RED, color);
                            }
                        } else if (select % 100 != 0) {
                            //베이스 라인
                            if ((selectIngerdients % 100) / 10 == 0) {
                                selectIngerdients += select;
                                Console::setBackground(color);
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(x, y);
                                Console::drawCursor(x, y, RED, color);
                            }
                        } else if (select % 1000 != 0) {
                            //시럽 라인
                            if ((selectIngerdients % 1000) / 100 == 0) {
                                selectIngerdients += select;
                                Console::setBackground(color);
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(x, y);
                                Console::drawCursor(x, y, RED, color);
                            }
                        } else if (select % 10000 != 0) {
                            //재료 라인
                            if ((selectIngerdients % 10000) / 1000 == 0) {
                                selectIngerdients += select;
                                Console::setBackground(color);
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(x, y);
                                Console::drawCursor(x, y, RED, color);
                            }
                        }
                    }
                }
            }

            iter = orderd.begin();
            successOrfail = true;
            totalPrice = 0;
            totalEx = 0;

            for (int i = 0; i < numberOfType && iter != orderd.end();
                 i++, iter++) {

                for (int j = 0; j < iter->second; j++) {

                    if (recipe[iter->first] != makeCoffee[i][j]) {
                        successOrfail = false;
                        totalPrice += coffeePrice[iter->first] * failPercnt;
                        failCount++;
                    } else {
                        totalPrice += coffeePrice[iter->first];
                        totalEx += ex[iter->first];
                        succesCount++;
                    }
                }
            }

            if (lastTime > lastTime / 2) {
                (successOrfail) ? page.workingPage3_day()
                                : page.workingPage4_day();
            } else {
                (successOrfail) ? page.workingPage3_night()
                                : page.workingPage4_night();
            }
            while (1) {
                if (Console::linux_getch() == ENTER)
                    break;
            }

            tempPrice = shmaddr[0] + totalPrice;
            tempSell = shmaddr[1] + totalCup;
            tempEx = shmaddr[2] + totalEx;
            memcpy(&shmaddr[0], &tempPrice, sizeof(int));
            memcpy(&shmaddr[1], &tempSell, sizeof(int));
            memcpy(&shmaddr[2], &tempEx, sizeof(int));
            memcpy(&shmaddr[3], &failCount, sizeof(int));
            memcpy(&shmaddr[4], &succesCount, sizeof(int));
        }
    } else {
        //게임 종료 후 데이터 저장
        shmaddr = (int *)shmat(id, NULL, SHM_RDONLY);
        wait(NULL);
        user.addMoney(shmaddr[0]);
        user.addCountsell(shmaddr[1]);
        user.addEx(shmaddr[2]);

        page.finish();
        //값
        Console::gotoXY(24, 11);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(shmaddr[1]).c_str(), LIGHTGRAY);
        Console::gotoXY(24, 13);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(shmaddr[3]).c_str(), LIGHTGRAY);
        Console::gotoXY(24, 15);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(user.getCountsell()).c_str(),
                                  LIGHTGRAY);
        Console::gotoXY(24, 17);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(shmaddr[0]).c_str(), LIGHTGRAY);
        Console::gotoXY(24, 19);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(user.getMoney()).c_str(),
                                  LIGHTGRAY);
        Console::gotoXY(52, 11);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(user.getlevel()).c_str(),
                                  LIGHTGRAY);
        Console::gotoXY(52, 13);
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(shmaddr[2]).c_str(), LIGHTGRAY);
        while (Console::linux_getch() != ENTER)
            ;
    }
    // 게임 종료 정보 출력
    shmdt(shmaddr);
    shmctl(id, IPC_RMID, NULL);
}

// Constructor
Store::Store(Page &_page) {
    page = _page; // 커서값이 있다고 생각하자
}

//상점 품목 표시
//커서 첫 위치 조정해야함
int Store::printItem(User &user) {

    Console::gotoXY(15, 11);
    Console::setBackground(LIGHTGRAY);
    if (!user.getRecipe(2)) { //구매기록없음
        if (user.getlevel() >= level[0]) {
            Console::printColorString("         1. 홍차             33000",
                                      CYAN);
        } else {
            Console::printColorString("[Locked] 1. 홍차             33000",
                                      CYAN);
        }
    } else { // 구매기록 있음
        Console::printColorString(" [Owned] 1. 홍차             33000", CYAN);
    }

    Console::gotoXY(15, 13);
    Console::setBackground(LIGHTGRAY);
    if (!user.getRecipe(3)) { //구매기록없음
        if (user.getlevel() >= level[1]) {
            Console::printColorString("        2. 카페모카          55000",
                                      LIGHTRED);

        } else {
            Console::printColorString("[Locked] 2. 카페모카         55000",
                                      LIGHTRED);
        }
    } else { // 구매기록 있음

        Console::printColorString(" [Owned] 2. 카페모카         55000",
                                  LIGHTRED);
    }

    Console::gotoXY(15, 15);
    Console::setBackground(LIGHTGRAY);
    if (!user.getRecipe(4)) { //구매기록없음
        if (user.getlevel() >= level[2]) {
            Console::printColorString("         3. 레몬 에이드      77000",
                                      YELLOW);
        } else {
            Console::printColorString("[Locked] 3. 레몬 에이드      77000",
                                      YELLOW);
        }
    } else { // 구매기록 있음
        Console::printColorString(" [Owned] 3. 레몬 에이드      77000", YELLOW);
    }

    Console::gotoXY(15, 17);
    Console::setBackground(LIGHTGRAY);
    if (!user.getRecipe(5)) { //구매기록없음
        if (user.getlevel() >= level[3]) {
            Console::printColorString("         4. 카라멜 마끼야또  99000",
                                      GREEN);
        } else {
            Console::printColorString("[Locked] 4. 카라멜 마끼야또  99000",
                                      GREEN);
        }
    } else { // 구매기록 있음
        Console::printColorString(" [Owned] 4. 카라멜 마끼야또  99000", GREEN);
    }

    return 0;
}

int Store::buyItem(User &user) {
    // 레시피를 소유하고 있지 않음
    int x = 13;
    int y = 11;
    char ch;

    while (1) {
        Console::gotoXY(x, y);
        Console::drawCursor(x, y, RED);
        // 키보드 입력
        while (1) { // 방향키 입력
            ch = Console::linux_getch();
            if (ch == ENTER) {
                break;
            } else if (ch == BACK) {
                return 1;
            } else {
                Console::linux_getch();
                ch = Console::linux_getch();
                if (ch == 'A') {
                    // UP
                    if (y > 11) {
                        y -= 2;
                        Console::drawCursor(x, y, RED);
                    }
                } else if (ch == 'B') {
                    // DOWN
                    if (y < 17) {
                        y += 2;
                        Console::drawCursor(x, y, RED);
                    }
                }
            }
        }

        Console::setBackground(LIGHTGRAY);
        switch (y) {
        case 11:
            if (user.getlevel() >= level[0] && user.getMoney() >= cost[0] &&
                user.getRecipe(0)) {
                Console::gotoXY(17, 19);
                string temp =
                    "잔액에서" + to_string(cost[0]) + "원이 차감됩니다.";
                Console::printColorString(temp.c_str(), BLACK);
                Console::gotoXY(17, 21);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("구매하시려면 Enter을 눌러주세요.",
                                          BLACK);
                Console::gotoXY(17, 23);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("아니라면 ESC를 눌러주세요", BLACK);

                ch = Console::linux_getch();
                if (ch == ENTER) {
                    ch = 'y';
                    user.addMoney(-cost[0]);
                    user.addRecipe(2);
                } else if (ch == ESC)
                    break;
            } else {
                Console::gotoXY(17, 19);
                Console::printColorString("구매 조건이 충족되지 않았습니다.",
                                          BLACK);
                while (Console::linux_getch() != ENTER) {
                };
            }
            break;
        case 13:
            if (user.getlevel() >= level[1] && user.getMoney() >= cost[1] &&
                user.getRecipe(1)) {
                Console::gotoXY(17, 19);
                string temp =
                    "잔액에서" + to_string(cost[1]) + "원이 차감됩니다.";
                Console::printColorString(temp.c_str(), BLACK);
                Console::gotoXY(17, 21);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("구매하시려면 Enter을 눌러주세요.",
                                          BLACK);
                Console::gotoXY(17, 23);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("아니라면 ESC를 눌러주세요", BLACK);

                ch = Console::linux_getch();
                if (ch == ENTER) {
                    ch = 'y';
                    user.addRecipe(3);
                    user.addMoney(-cost[1]);
                } else if (ch == ESC)
                    break;
            } else {
                Console::gotoXY(17, 19);
                Console::printColorString("구매 조건이 충족되지 않았습니다.",
                                          BLACK);
                while (Console::linux_getch() != ENTER) {
                };
            }
            break;
        case 15:
            if (user.getlevel() >= level[2] && user.getMoney() >= cost[2] &&
                user.getRecipe(2)) {
                Console::gotoXY(17, 19);
                string temp =
                    "잔액에서" + to_string(cost[2]) + "원이 차감됩니다.";
                Console::printColorString(temp.c_str(), BLACK);
                Console::gotoXY(17, 21);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString(
                    "구매하시려면 Enter 자판을 눌러주세요.", BLACK);
                Console::gotoXY(17, 23);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("아니라면 ESC를 눌러주세요", BLACK);

                ch = Console::linux_getch();
                if (ch == ENTER) {
                    ch = 'y';
                    user.addRecipe(4);
                    user.addMoney(-cost[2]);
                } else if (ch == ESC)
                    break;
            } else {
                Console::gotoXY(17, 19);
                Console::printColorString("구매 조건이 충족되지 않았습니다.",
                                          BLACK);
                while (Console::linux_getch() != ENTER) {
                };
            }
            break;
        case 17:
            if (user.getlevel() >= level[3] && user.getMoney() >= cost[3] &&
                user.getRecipe(3)) {
                Console::gotoXY(17, 19);
                string temp =
                    "잔액에서" + to_string(cost[3]) + "원이 차감됩니다.";
                Console::printColorString(temp.c_str(), BLACK);
                Console::gotoXY(17, 21);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString(
                    "구매하시려면 Enter 자판을 눌러주세요.", BLACK);
                Console::gotoXY(17, 23);
                Console::setBackground(LIGHTGRAY);
                Console::printColorString("아니라면 ESC를 눌러주세요", BLACK);

                ch = Console::linux_getch();
                if (ch == ENTER) {
                    ch = 'y';
                    user.addRecipe(5);
                    user.addMoney(-cost[3]);
                } else if (ch == ESC)
                    break;

            } else {
                Console::gotoXY(17, 19);
                Console::printColorString("구매 조건이 충족되지 않았습니다.",
                                          BLACK);
                while (Console::linux_getch() != ENTER) {
                };
            }
            break;
        }

        //지우기
        Console::gotoXY(17, 19);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("                                 ", BLACK);
        Console::gotoXY(17, 21);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("                                   ", BLACK);
        Console::gotoXY(17, 23);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("                                 ", BLACK);
        if (ch == 'y')
            break;
    }
    return 0;
}

Minigame::Minigame(Page &_page) { page = _page; }

// 그럼 나는 선택해야할 거야
int Minigame::wantGame() {

    page.minigame1();

    while (1) {
        for (int i = 5; i < 62; i++) {
            for (int j = 11; j < 24; j++) {
                Console::printDot(i, j, MAGENTA);
            }
        }

        Console::gotoXY(20, 9);
        Console::setBackground(MAGENTA);
        Console::printColorString(" ▶ DO YOU WANNT START? ◀  ", LIGHTGRAY);

        Console::gotoXY(15, 15);
        Console::setBackground(MAGENTA);
        Console::printColorString("가위바위보가 열리는 미니게임장입니다.");
        Console::gotoXY(20, 17);
        Console::setBackground(MAGENTA);
        Console::printColorString("게임을 진행하시겠습니까? (y/n)");
        Console::gotoXY(24, 19);
        Console::setBackground(MAGENTA);
        Console::printColorString("입력 : ");
        Console::gotoXY(34, 19);

        Console::setBackground(MAGENTA);
        string temp = Console::input(0, 1);
        if (temp == "n")
            return 0;
        else if (temp == "y")
            break;
    }
    return 1;
}

int Minigame::wantBatting(User &user) {
    string input;
    int money;

    for (int i = 5; i < 62; i++) {
        for (int j = 11; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }

    Console::gotoXY(21, 9);
    Console::setBackground(MAGENTA);
    Console::printColorString(" ▶ READY FOR THE GAME ◀  ", LIGHTGRAY);

    Console::gotoXY(17, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("미니게임에 오신 것을 환영합니다.");
    Console::gotoXY(10, 15);
    Console::setBackground(MAGENTA);
    Console::printColorString("게임에서 이길 시, 배팅 금액의 1.5~2.0배를 받고");
    Console::gotoXY(12, 17);
    Console::setBackground(MAGENTA);
    Console::printColorString("게임에서 질 시, 배팅 금액을 모두 잃습니다.");
    Console::gotoXY(14, 19);
    Console::setBackground(MAGENTA);
    Console::printColorString("(ENTER 입력 시 다음 화면으로 이동합니다.)");
    Console::gotoXY(31, 21);
    while (Console::linux_getch() != ENTER)
        ;

    while (1) {
        for (int i = 5; i < 62; i++) {
            for (int j = 11; j < 24; j++) {
                Console::printDot(i, j, MAGENTA);
            }
        }

        Console::gotoXY(21, 9);
        Console::setBackground(MAGENTA);
        Console::printColorString(" ▶ READY FOR THE GAME ◀  ", LIGHTGRAY);

        Console::gotoXY(15, 13);
        Console::setBackground(MAGENTA);
        Console::printColorString("얼마를 배팅하시겠습니까?");
        Console::gotoXY(15, 15);
        Console::setBackground(MAGENTA);
        Console::printColorString("현재 소유 금액 : ");
        Console::setBackground(MAGENTA);
        Console::printColorString(to_string(user.getMoney()).c_str(), BLACK);

        Console::gotoXY(15, 17);
        Console::setBackground(MAGENTA);
        Console::printColorString("배팅 금액 입력 : ");
        Console::setBackground(MAGENTA);
        input = Console::input(3);
        money = stoi(input);

        if (money > user.getMoney()) {
            Console::gotoXY(25, 21);
            Console::setBackground(MAGENTA);
            Console::printColorString("잘못된 금액입니다.");
            Console::gotoXY(25, 23);
            Console::setBackground(MAGENTA);
            Console::printColorString("다시 입력합니다.");
            while (Console::linux_getch() != ENTER)
                ;
        } else {
            break;
        }
    }
    while (1) {
        Console::gotoXY(11, 20);
        Console::setBackground(MAGENTA);
        Console::printColorString(
            "(n 입력시 미니 게임 처음 화면으로 돌아갑니다)");

        Console::gotoXY(15, 19);
        Console::setBackground(MAGENTA);
        Console::printColorString("배팅을 진행하겠습니까?(y/n) : ");

        Console::setBackground(MAGENTA);
        input = Console::input(0, 1);
        if (input == "n")
            return -1;

        Console::gotoXY(20, 23);
        Console::setBackground(MAGENTA);
        Console::printColorString(" ▶ 게임을 시작합니다. ◀  ");
        while (Console::linux_getch() != ENTER)
            ;
        break;
    }
    gamebleMoney = money;

    return money;
}

int Minigame::startGame(User &user) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> com(1, 3);
    string input;
    int userNum;

    int comNum = com(gen);

    Console::gotoXY(11, 9);
    Console::setBackground(LIGHTRED);

    // 사용자는 어떤걸 낼까
    page.minigame2();
    while (1) {
        Console::gotoXY(6, 9);
        Console::setBackground(LIGHTRED);
        Console::printColorString("        ");
        Console::gotoXY(6, 9);
        Console::setBackground(LIGHTRED);
        Console::printColorString("입력 :");
        input = Console::input(3);
        userNum = stoi(input);
        if (userNum > 0 && userNum < 4) {
            break;
        }
    }

    if (comNum == 1) {      // 컴퓨터 - > 가위
        if (userNum == 1) { // 유저 -> 가위
            sameGame(user);
        } else if (userNum == 2) { // 유저 -> 바위
            winGame(user);
        } else if (userNum == 3) { // 유저 -> 보
            loseGame(user);
        }
    } else if (comNum == 2) { //컴퓨터 - > 바위
        if (userNum == 1) {   // 유저 -> 가위
            loseGame(user);
        } else if (userNum == 2) { // 유저 -> 바위
            sameGame(user);
        } else if (userNum == 3) { // 유저 -> 보
            winGame(user);
        }
    } else if (comNum == 3) { //컴퓨터 - > 보
        if (userNum == 1) {   // 유저 -> 가위
            winGame(user);
        } else if (userNum == 2) { // 유저 -> 바위
            loseGame(user);
        } else if (userNum == 3) { // 유저 -> 보
            sameGame(user);
        }
    }

    while (Console::linux_getch() != ENTER)
        ;
}

int Minigame::winGame(User &user) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> per(1.5, 2.0);
    double percent;
    int money;

    page.minigame3();
    percent = per(gen);
    string text = "배팅 금액의 " + to_string(percent) + " 배가 주어집니다.";
    Console::gotoXY(18, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString(text.c_str());

    // reward box
    for (int i = 18; i < 49; i++) {
        Console::printDot(i, 15, LIGHTRED);
        for (int j = 16; j < 22; j++) {
            Console::printDot(i, j, LIGHTGRAY);
        }
    }

    money = gamebleMoney * percent;
    user.addMoney(money);

    Console::gotoXY(30, 15);
    Console::setBackground(LIGHTRED);
    Console::printColorString("REWARD", LIGHTGRAY);
    Console::gotoXY(24, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("받은 금액 :", LIGHTRED);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(money).c_str(), LIGHTRED);

    Console::gotoXY(24, 19);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("현재 잔고 :", LIGHTRED);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getMoney()).c_str(), LIGHTRED);
}

int Minigame::sameGame(User &user) {
    user.addMoney(-gamebleMoney);
    Console::gotoXY(24, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("잃은 금액 :", YELLOW);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(gamebleMoney).c_str(), LIGHTRED);
    Console::gotoXY(24, 19);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("현재 잔고 :", YELLOW);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getMoney()).c_str(), LIGHTRED);
}

int Minigame::loseGame(User &user) {
    // result box
    for (int i = 5; i < 62; i++) {
        for (int j = 9; j < 24; j++) {
            Console::printDot(i, j, MAGENTA);
        }
    }
    Console::gotoXY(22, 11);
    Console::setBackground(MAGENTA);
    Console::printColorString("당신은 게임에서 졌습니다.");
    Console::gotoXY(20, 13);
    Console::setBackground(MAGENTA);
    Console::printColorString("배팅 금액의 모두를 잃습니다.");

    // penalty box
    for (int i = 18; i < 49; i++) {
        Console::printDot(i, 15, BLUE);
        for (int j = 16; j < 22; j++) {
            Console::printDot(i, j, LIGHTGRAY);
        }
    }

    user.addMoney(-gamebleMoney);
    Console::gotoXY(30, 15);
    Console::setBackground(BLUE);
    Console::printColorString("PENALTY");
    Console::gotoXY(24, 17);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("잃은 금액 :", BLUE);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(gamebleMoney).c_str(), LIGHTRED);

    Console::gotoXY(24, 19);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("현재 잔고 :", BLUE);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getMoney()).c_str(), LIGHTRED);
}

void showMyInfo(Page &page, User &user) {
    page.myInfo();

    Console::gotoXY(9, 10);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 이름 ]          ", CYAN);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(user.getName().c_str(), CYAN);

    Console::gotoXY(9, 12);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 레벨 ]          ", MAGENTA);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("Lv.", MAGENTA);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getlevel()).c_str(), MAGENTA);

    Console::gotoXY(9, 14);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 성취도 ]        ", YELLOW);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getCurEx()).c_str(), YELLOW);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" Ex", YELLOW);

    Console::gotoXY(9, 16);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 습득 레시피 ]   ", GREEN);
    Console::setBackground(LIGHTGRAY);
    if (user.getRecipe(0)) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("아메리카노 ", GREEN);
    }

    if (user.getRecipe(1)) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("카페라떼 ", GREEN);
    }

    if (user.getRecipe(2)) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("홍차", GREEN);
    }

    if (user.getRecipe(3)) {
        Console::gotoXY(29, 18);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("카페모카 ", GREEN);
    }

    if (user.getRecipe(4)) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("레몬에이드 ", GREEN);
    }

    if (user.getRecipe(5)) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("카라멜마끼아또 ", GREEN);
    }

    int y = (user.getlevel() > 2) ? 20 : 18;

    Console::gotoXY(9, y);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 소유금 ]        ", LIGHTRED);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getMoney()).c_str(), LIGHTRED);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" 원", LIGHTRED);

    Console::gotoXY(9, y + 2);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString("- [ 판매 잔수 ]     ", GRAY);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(to_string(user.getCountsell()).c_str(), GRAY);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(" 잔", GRAY);

    if (user.getlevel() > 4) {
        Console::printDot(48, 6, YELLOW);
        Console::printDot(49, 6, LIGHTCYAN);
        Console::printDot(50, 6, YELLOW);
        Console::printDot(51, 6, LIGHTCYAN);
        Console::printDot(52, 6, YELLOW);
        Console::printDot(53, 6, LIGHTCYAN);
        Console::printDot(54, 6, YELLOW);
        Console::printDot(55, 6, LIGHTCYAN);
        Console::printDot(56, 6, YELLOW);
        Console::printDot(57, 6, LIGHTCYAN);
        Console::printDot(58, 6, YELLOW);

        for (int i = 48; i < 59; i++) {
            Console::printDot(i, 5, LIGHTYELLOW);
        }

        Console::printDot(53, 4, LIGHTRED);
        Console::printDot(48, 4, LIGHTYELLOW);
        Console::printDot(49, 4, LIGHTYELLOW);
        Console::printDot(50, 4, LIGHTYELLOW);
        Console::printDot(51, 4, LIGHTYELLOW);
        Console::printDot(52, 4, LIGHTYELLOW);
        Console::printDot(54, 4, LIGHTYELLOW);
        Console::printDot(55, 4, LIGHTYELLOW);
        Console::printDot(56, 4, LIGHTYELLOW);
        Console::printDot(57, 4, LIGHTYELLOW);
        Console::printDot(58, 4, LIGHTYELLOW);

        Console::printDot(49, 3, LIGHTYELLOW);
        Console::printDot(52, 3, LIGHTYELLOW);
        Console::printDot(53, 3, LIGHTYELLOW);
        Console::printDot(54, 3, LIGHTYELLOW);
        Console::printDot(57, 3, LIGHTYELLOW);

        Console::printDot(53, 2, LIGHTYELLOW);
    }
    while (Console::linux_getch() != ENTER)
        ;
}

void showRanking(Page &page, User &user) {
    struct stat fileInfo;
    DIR *dirp;
    struct dirent *dirInfo;
    int fd;
    char temp[10];
    ssize_t rsize;

    string sell = "";
    string lv = "";
    string sellPath;
    string lvPath;
    string dataPath = user.getDataPath();
    multimap<int, string> ranking;
    multimap<int, string>::iterator iter;
    int i;

    close(fd);

    dirp = opendir(dataPath.c_str());
    while ((dirInfo = readdir(dirp)) != NULL) {
        if (strcmp(dirInfo->d_name, ".") != 0 &&
            strcmp(dirInfo->d_name, "..") != 0) {
            sellPath = dataPath + "/" + dirInfo->d_name + "/sell.txt";
            fd = open(sellPath.c_str(), O_RDONLY);

            sell.clear();
            do {
                memset(temp, '\0', 10);
                rsize = read(fd, (char *)temp, sizeof(temp));
                sell += temp;
            } while (rsize > 0);
        }

        ranking.insert(pair<int, string>(stoi(sell), dirInfo->d_name));
    }

    page.ranking();

    iter = ranking.end()--;
    iter--;
    i = 1;
    while (i < 6) {
        lvPath = dataPath + "/" + iter->second + "/level.txt";
        fd = open(lvPath.c_str(), O_RDONLY);

        lv.clear();
        do {
            memset(temp, '\0', 10);
            rsize = read(fd, (char *)temp, sizeof(temp));
            lv += temp;
        } while (rsize > 0);

        if (i == 1) {
            // rank 1st
            Console::gotoXY(13, 14);
            Console::setBackground(MAGENTA);
            Console::printColorString("1ST", LIGHTRED);

            Console::gotoXY(25, 14);
            Console::setBackground(MAGENTA);
            Console::printColorString(iter->second.c_str(), LIGHTRED);

            Console::gotoXY(37, 14);
            Console::setBackground(MAGENTA);
            Console::printColorString("LV.", LIGHTRED);
            Console::setBackground(MAGENTA);
            Console::printColorString(lv.c_str(), LIGHTRED);

            Console::gotoXY(49, 14);
            Console::setBackground(MAGENTA);
            Console::printColorString(to_string(iter->first).c_str(), LIGHTRED);
        } else if (i == 2) {
            // rank 2nd
            Console::gotoXY(13, 16);
            Console::setBackground(MAGENTA);
            Console::printColorString("2ND", LIGHTYELLOW);

            Console::gotoXY(25, 16);
            Console::setBackground(MAGENTA);
            Console::printColorString(iter->second.c_str(), LIGHTYELLOW);

            Console::gotoXY(37, 16);
            Console::setBackground(MAGENTA);
            Console::printColorString("LV.", LIGHTYELLOW);
            Console::setBackground(MAGENTA);
            Console::printColorString(lv.c_str(), LIGHTYELLOW);

            Console::gotoXY(49, 16);
            Console::setBackground(MAGENTA);
            Console::printColorString(to_string(iter->first).c_str(),
                                      LIGHTYELLOW);
        } else if (i == 3) {
            // rank 3rd
            Console::gotoXY(13, 18);
            Console::setBackground(MAGENTA);
            Console::printColorString("3RD", LIGHTGREEN);

            Console::gotoXY(25, 18);
            Console::setBackground(MAGENTA);
            Console::printColorString(iter->second.c_str(), LIGHTGREEN);

            Console::gotoXY(37, 18);
            Console::setBackground(MAGENTA);
            Console::printColorString("LV.", LIGHTGREEN);
            Console::setBackground(MAGENTA);
            Console::printColorString(lv.c_str(), LIGHTGREEN);

            Console::gotoXY(49, 18);
            Console::setBackground(MAGENTA);
            Console::printColorString(to_string(iter->first).c_str(),
                                      LIGHTGREEN);
        } else if (i == 4) {
            // rank 4th
            Console::gotoXY(13, 20);
            Console::setBackground(MAGENTA);
            Console::printColorString("4th", LIGHTGRAY);

            Console::gotoXY(25, 20);
            Console::setBackground(MAGENTA);
            Console::printColorString(iter->second.c_str(), LIGHTGRAY);

            Console::gotoXY(37, 20);
            Console::setBackground(MAGENTA);
            Console::printColorString("LV.", LIGHTGRAY);
            Console::setBackground(MAGENTA);
            Console::printColorString(lv.c_str(), LIGHTGRAY);

            Console::gotoXY(49, 20);
            Console::setBackground(MAGENTA);
            Console::printColorString(to_string(iter->first).c_str(),
                                      LIGHTGRAY);
        } else if (i == 5) {
            // rank 5th
            Console::gotoXY(13, 22);
            Console::setBackground(MAGENTA);
            Console::printColorString("5th", LIGHTGRAY);

            Console::gotoXY(25, 22);
            Console::setBackground(MAGENTA);
            Console::printColorString(iter->second.c_str(), LIGHTGRAY);

            Console::gotoXY(37, 22);
            Console::setBackground(MAGENTA);
            Console::printColorString("LV.", LIGHTGRAY);
            Console::setBackground(MAGENTA);
            Console::printColorString(lv.c_str(), LIGHTGRAY);

            Console::gotoXY(49, 22);
            Console::setBackground(MAGENTA);
            Console::printColorString(to_string(iter->first).c_str(),
                                      LIGHTGRAY);
        }

        if (iter == ranking.begin())
            break;
        i++;
        iter--;
    }

    Console::linux_getch();
}
