#include "perform.hpp"
#include "console.hpp"
#include "user.hpp"
#include <cstring>
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

int Game::lastTime = 100;

void *showTime(void *) {
    for (int i = 0; i < 60; i++) {
        sleep(1);
        Game::lastTime--;
    }
}

void Game::start(User &user) {
    int pid; // 첫 번쨰 pid
    key_t key;
    int id;
    int *shmaddr = NULL; // 0:금액, 1:잔수, 2:경험치
    lastTime = 100;

    string checkShowRecipe;

    key = ftok("./main.cpp", 1);
    id = shmget(key, MAX_SIZE, IPC_CREAT | 0600);

    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
        return;
    } else if (pid == 0) {
        //게임 종료 후 데이터 저장
        shmaddr = (int *)shmat(id, NULL, SHM_RDONLY);
        waitpid(pid, NULL, 0);
        user.addMoney(shmaddr[0]);
        user.addCountsell(shmaddr[1]);
        user.addEx(shmaddr[2]);
    } else {
        // 데이터 통신
        shmaddr = (int *)shmat(id, NULL, 0);
        memset(shmaddr, 0, sizeof(shmaddr));
        //게임 진행
        map<int, int> orderd; // 커피 종류 및 수량 저장
        int numberOfType;     // 커피 종류 개수
        int kind;             // 커피 종류
        int showSelectY = 10;
        int color;

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
        map<int, int>::iterator c_end;

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

        char ch; // 키보드 입력

        //난수 생성
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> randNumberOfType(1, 2);   // 종류 개수
        uniform_int_distribution<int> randQuantity(1, 5);       // 주문 개수
        uniform_int_distribution<int> randKindOfType(0, level); //커피 종류

        //타이머 설정
        // alarm(100);

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

            numberOfType = randNumberOfType(gen);

            // 메뉴 주문
            for (int i = 0; i < numberOfType; i++) {
                kind = randKindOfType(gen);
                c_end = orderd.end();
                if (user.getRecipe(kind) && orderd.find(kind) == c_end) {
                    orderd[kind] = randQuantity(gen);
                    totalCup += orderd[kind];
                } else {
                    i--;
                }
            }

            color = LIGHTGRAY;
            //주문 정보 출력
            if (lastTime > 50) {
                page.workingPage1_day(orderd);
            } else {
                page.workingPage1_night(orderd);
            }

            // ------ 디자인 변경 필요 -----
            //레시피 출력 여부
            page.showRecipeButton();
            cin >> checkShowRecipe;

            if (checkShowRecipe == "y") {
                // ------ 디자인 변경 필요 -----
                int tempY = 8;
                page.showRecipe();

                //레시피 출력
                for (iter = orderd.begin(); iter != orderd.end(); iter++) {
                    Console::gotoXY(7, tempY++);
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
                sleep(10); //보여주는 시간
            }

            // ------ 디자인 변경 필요 -----
            // 재료 선택을 위해 재료 보여주기
            for (vector<string> v : ingerdients) {
                for (string item : v) {
                    cout << item << " ";
                }
                cout << endl;
            }

            page.makingDrink(orderd, level);
            Console::linux_getch(); //입력 버퍼에 남아있는 엔터키 제거
            //배열 초기화

            int x = 4;
            int y = 12;
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
                            if (ch == ENTER) {
                                ch = 'y';
                                break;
                            } else if (ch == SPACE) {
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
                                            select -= 2;
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
                                        select += 2;
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
                                        select *= 10;
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
                                        select /= 10;
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
                            //좌표 초기화
                            x = 4;
                            y = 12;

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
                    } else {
                        totalPrice += coffeePrice[iter->first];
                        totalEx += ex[iter->first];
                    }
                }
            }

            if (lastTime > 50) {
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
            //-----------test--------
            cout << "totalPrice : " << totalPrice
                 << ", countSell : " << totalCup << endl;
            tempPrice = shmaddr[0] + totalPrice;
            tempSell = shmaddr[1] + totalCup;
            tempEx = shmaddr[2] + totalEx;
            memcpy(&shmaddr[0], &tempPrice, sizeof(int));
            memcpy(&shmaddr[1], &tempSell, sizeof(int));
            memcpy(&shmaddr[2], &totalEx, sizeof(int));
        }
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
    if (user.getRecipe(2) == 0) { //구매기록없음
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
    if (user.getRecipe(3) == 0) { //구매기록없음
        if (user.getlevel() >= level[1]) {
            Console::printColorString("         2. 레몬 에이드      55000",
                                      YELLOW);
        } else {
            Console::printColorString(" [Locked] 2. 레몬 에이드      55000",
                                      YELLOW);
        }
    } else { // 구매기록 있음
        Console::printColorString(" [Owned] 2. 레몬 에이드      55000", YELLOW);
    }

    Console::gotoXY(15, 15);
    Console::setBackground(LIGHTGRAY);
    if (user.getRecipe(4) == 0) { //구매기록없음
        if (user.getlevel() >= level[2]) {
            Console::printColorString("        3. 카페모카          77000",
                                      LIGHTRED);
        } else {
            Console::printColorString("[Locked] 3. 카페모카         77000",
                                      LIGHTRED);
        }
    } else { // 구매기록 있음
        Console::printColorString(" [Owned] 3. 카페모카         77000",
                                  LIGHTRED);
    }

    Console::gotoXY(15, 17);
    Console::setBackground(LIGHTGRAY);
    if (user.getRecipe(5) == 0) { //구매기록없음
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
            if (user.getlevel() >= level[0] && user.getMoney() >= cost[0]) {
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
            if (user.getlevel() >= level[1] && user.getMoney() >= cost[1]) {
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
            if (user.getlevel() >= level[2] && user.getMoney() >= cost[2]) {
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
            if (user.getlevel() >= level[3] && user.getMoney() >= cost[3]) {
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

Minigame::Minigame() { wantGame(); }
//미니게임 UI 출력

// 그럼 나는 선택해야할 거야
int Minigame::wantGame() {
    string input;

    while (1) {
        cout << "가위바위보가 열리는 미니게임장입니다. 게임을 "
                "진행하시겠습니까?(y/n)"
             << endl;
        cout << "시작하려면 y, 메뉴로 돌아가시려면 n을 입력하세요" << endl;
        cin >> input;

        if (input == "y") {
            //이거 그냥 내가 보고면서 하고자 써둠 ! 이런 프로세스를 생각하면서
            //했음
            cout << "미니게임에 오신 것을 환영합니다." << endl;
            cout
                << "본 미니게임은 가위바위보의 승패 여부에 따라 돈을 늘릴수도, "
                   "잃을 수도 있습니다. "
                << endl;
            cout << "가위바위보에서 이길 시, 배팅한 금액의 1.0~2.0배의 돈을 "
                    "받을 "
                    "수 있습니다. "
                 << endl;
            cout << "그러나 가위바위보에서 졌을 경우 배팅한 금액을 모두 "
                    "잃게됩니다."
                 << endl;
            wantBatting();
            break;
        } else if (input == "n") {
            break;
        } else {
            cout << "잘못된 입력입니다. 다시 시도하세요" << endl;
        }
    }
    return 0;
}

int Minigame::wantBatting() {
    string input;

    while (1) {
        cout << "얼마를 배팅하시겠습니까? 자신이 소유한 잔고 내에서만 "
                "가능합니다. "
             << endl;
        cout << "( 현재 소유 금액 :" << user_money << "원 )" << endl;
        cin >> gamble_money;

        cout << "배팅하고자 하는 금액이 " << gamble_money << "원 이 맞습니까?"
             << endl;
        cin >> input;

        if (input == "y") {
            cout << "게임을 시작합니다." << endl;
            break;
        }
        if (input == "n") {
            cout << "다시 입력합니다." << endl;
        } else {
            cout << "잘못된 입력입니다. 다시 시도하세요" << endl;
        }
    }
    startGame();
    return 0;
}

int Minigame::startGame() {
    static unsigned int seed = 9876;
    int random_num = (rand() % 20) / 10;
    int com_num = (rand() % 3) + 1;

    // 사용자는 어떤걸 낼까
    int input;
    cout << "가위바위보 게임을 진행합니다. " << endl;
    cout << "1. 가위/ 2. 바위/ 3. 보 중에 선택하세요(숫자만 입력)" << endl;
    cin >> input;
    // 컴퓨터는 어떤걸 낼까
    if (com_num = 1) {    // 컴퓨터 - > 가위
        if (input == 1) { // 유저 -> 가위
            sameGame(random_num);
        } else if (input == 2) { // 유저 -> 바위
            winGame(random_num);
        } else if (input == 3) { // 유저 -> 보
            loseGame(random_num);
        }
    } else if (com_num = 2) { //컴퓨터 - > 바위
        if (input == 1) {     // 유저 -> 가위
            loseGame(random_num);
        } else if (input == 2) { // 유저 -> 바위
            sameGame(random_num);
        } else if (input == 3) { // 유저 -> 보
            winGame(random_num);
        }

    } else if (com_num = 3) { //컴퓨터 - > 보
        if (input == 1) {     // 유저 -> 가위
            winGame(random_num);
        } else if (input == 2) { // 유저 -> 바위
            loseGame(random_num);
        } else if (input == 3) { // 유저 -> 보
            sameGame(random_num);
        }
    }
}

int Minigame::winGame(int random_num) {
    cout << "이겼습니다." << endl;
    cout << "게임에 배팅한 돈" << gamble_money << "원 의" << random_num
         << "배인" << gamble_money * random_num << "원 을 받습니다.";
}

int Minigame::sameGame(int random_num) {
    cout << "비겼습니다." << endl;
    cout << "게임에 배팅한 돈" << gamble_money << "원을 잃었습니다." << endl;
    user_money -= gamble_money;
    cout << "현재 잔고는" << user_money << "원 니다." << endl;
}

int Minigame::loseGame(int random_num) {
    cout << "졌습니다." << endl;
    cout << "게임에 배팅한 돈" << gamble_money << "원을 잃었습니다." << endl;
    user_money -= gamble_money;
    cout << "현재 잔고는" << user_money << "원 입니다." << endl;
}
