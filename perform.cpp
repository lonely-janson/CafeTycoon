#include "perform.hpp"
#include "console.hpp"
#include "user.hpp"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <pthread.h>
#include <pwd.h>
#include <queue>
#include <random>
#include <signal.h>
#include <stack>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

using namespace std;

#define PERMS 0755

Data::Data() {

    struct passwd *info;

    if (((info = getpwuid(getuid())) == NULL)) {
        perror("getpwuid() error!");
        exit(-1);
    }

    dataPath = "/home/";
    dataPath += info->pw_name;
    dataPath += "/Data/";

    if (access(dataPath.c_str(), F_OK) == -1) {
        //폴더가 존재하지 않을시;
        if (mkdir(dataPath.c_str(), PERMS) == -1) {
            perror("mkdir() error!");
            exit(-2);
        }
    }

    ranking = dataPath + "/ranking";
    if (access(ranking.c_str(), F_OK) == -1) {
        if (mkdir(ranking.c_str(), PERMS) == -1) {
            perror("mkdir() error!");
            exit(-2);
        }
    }
}

bool Data::signUp() {
    string id;
    string pw;
    string userSell;
    string userRanking;
    string userLevel;

    string pwPath;
    string userRankingPath;
    string userSellPath;
    string userLevelPath;

    int fd = 0;
    ssize_t wsize;

    // 아이디 입력
    while (1) {
        cout << "ID : ";
        id = dataPath;
        id += Console::input();

        if (mkdir(id.c_str(), PERMS) == -1) {
            cout << "already exiting id";
        } else {
            break;
        }
    }

    // 비밀번호 입력
    cout << "PW : ";
    pw = Console::input(1);
    pwPath = id + "/pw.dat";

    fd = open(pwPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    if (fd == -1) {
        cout << "Sign Up error please Retry";
        perror("open() error!");
        rmdir(id.c_str());
        return false;
    }

    wsize = write(fd, (char *)pw.c_str(), pw.length());

    close(fd);

    if (wsize == -1) {
        cout << "Sign Up error please Retry";
        perror("write() error!");
        remove(pwPath.c_str());
        rmdir(id.c_str());
        return false;
    }

    userRankingPath = ranking + "/user_id";
    mkdir(userRankingPath.c_str(), 0644);

    userSellPath = userRanking + "usersell.txt";
    userSell = "0";
    fd = open(userSellPath.c_str(), O_CREAT | O_TRUNC | O_RDWR, PERMS);
    write(fd, (char *)userSell.c_str(), strlen(userSell.c_str()));

    userLevelPath = userRanking + "userlevel.txt";
    userLevel = "0";
    fd = open(userLevelPath.c_str(), O_CREAT | O_TRUNC | O_RDWR, PERMS);
    write(fd, (char *)userLevel.c_str(), strlen(userLevel.c_str()));

    return true;
}

bool Data::signIn() {
    string id;
    string pw;
    string originPw;
    string pwPath;
    char *temp;
    int pwCount = 0;
    int idCount = 0;

    int fd = 0;
    struct stat fileinfo;

    // 아이디 입력
    while (1) {
        if (idCount++ > 5)
            return false;
        cout << "ID : ";
        id = dataPath;
        id += Console::input();

        if (access(dataPath.c_str(), F_OK) != -1) {
            //폴더가 존재할떄
            break;
        }
    }

    //비밀번호 불러오기;

    pwPath = id + "/pw.dat";
    fd = open(pwPath.c_str(), O_RDONLY);

    if (fd == -1) {
        cout << "Sign In error please Retry";
        perror("open() error!");
        return false;
    }

    if (fstat(fd, &fileinfo) == -1) {
        cout << "Sign In error please Retry";
        perror("fstat() error!");
        return false;
    }

    temp = (char *)malloc(fileinfo.st_size);
    if (read(fd, (char *)temp, fileinfo.st_size) == -1) {
        cout << "Sign In error please Retry";
        perror("read() error!");
        return false;
    }
    originPw = temp;
    close(fd);

    //비밀번호 입력
    while (1) {
        if (pwCount++ > 5)
            return false;

        cout << "PW : ";
        pw = Console::input(1);

        if (pw == originPw)
            break;
    }

    return true;
}

void gameOver(int signum) {
    int status;
    //게임종료 창 보여주기
    cout << "gameOver\n";
    exit(0);
}

void *showTime(void *) {
    for (int i = 0; i < 60; i++) {
        sleep(1);
        Console::gotoXY(5, HEIGHT);
        Console::setBackground(LIGHTMAGENTA);
        Console::printColorString(to_string(i).c_str(), LIGHTYELLOW);

        Console::gotoXY(selectX, selectY);
    }
}

void Game::start(User &user) {
    int pid; // 첫 번쨰 pid
    key_t key;
    int id;
    int *shmaddr = NULL; // 0:금액, 1:잔수, 2:경험치

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

            // ------ 디자인 변경 필요 -----
            //주문 정보 출력
            page.workingPage1_day(orderd);

            // ------ 디자인 변경 필요 -----
            //레시피 출력 여부
            cout << "Do you want show recepie? : ";
            cin >> checkShowRecipe;

            if (checkShowRecipe == "y") {
                // ------ 디자인 변경 필요 -----
                //레시피 출력
                for (iter = orderd.begin(); iter != orderd.end(); iter++) {
                    switch (iter->first) {
                    case 0:
                        cout << "Americano : shot(2), water" << endl;
                        break;
                    case 1:
                        cout << "Cafe Lattee : shot(2), milk" << endl;
                        break;
                    case 2:
                        cout << "Cafe Lattee : black tea bag, water" << endl;
                        break;
                    case 3:
                        cout << "Cafe Mocha : mocha syrup, shot(2), milk "
                             << endl;
                        break;
                    case 4:
                        cout << "Lemonade : shot(2), milk" << endl;
                        break;
                    case 5:
                        cout << "Carame Macchiato : caramel syrup, mikl, "
                                "shot(2), "
                                "carmel drizzle"
                             << endl;
                        break;
                    }
                }
                sleep(0); //보여주는 시간
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

            int drinkingCount = 1;
            int syrupLevel = (level > 4) ? 4 : level;
            select = 1;
            selectX = 4;
            selectY = 12;

            iter = orderd.begin();
            for (int i = 0; iter != orderd.end(); iter++, i++) {
                for (int j = 0; j < iter->second; j++) {
                    Console::gotoXY(26, 5);
                    Console::setBackground(LIGHTGRAY);
                    Console::printColorString(coffeeName[iter->first].c_str(),
                                              MAGENTA);

                    string drinkCountStr = "(" + to_string(drinkingCount);
                    drinkCountStr += '/';
                    drinkCountStr += to_string(totalCup) + ")";
                    drinkingCount++;
                    Console::gotoXY(58, 4);
                    Console::setBackground(LIGHTGRAY);
                    Console::printColorString("      ", MAGENTA);
                    Console::gotoXY(58, 4);
                    Console::setBackground(LIGHTGRAY);
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
                                    if (selectY > 12) {
                                        //재료 라인
                                        selectY -= 2;
                                        if (selectX == 4)
                                            select -= 2;
                                        if (selectX == 14)
                                            select -= 20;
                                        if (selectX == 25)
                                            select -= 200;
                                        if (selectX == 36)
                                            select -= 2000;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    }
                                } else if (ch == 'B') {
                                    // DOWN
                                    if (selectX == 4 && selectY < 16) {
                                        //재료 라인
                                        selectY += 2;
                                        select += 2;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 14 &&
                                               selectY < 14 + (level / 3) * 2) {
                                        // 베이스 라인
                                        selectY += 2;
                                        select += 20;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 25 &&
                                               selectY <
                                                   12 + (syrupLevel - 2) * 2) {
                                        // 시럽 라인
                                        selectY += 2;
                                        select += 200;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 36 &&
                                               selectY < 12 + (level - 3) * 2) {
                                        // 재료 라인
                                        selectY += 2;
                                        select += 2000;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    }
                                } else if (ch == 'C') { // RIGHT
                                    if (selectX == 4) {
                                        //샷 라인
                                        selectX = 14;
                                        select *= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 14) {
                                        //베이스 라인
                                        selectX = 25;
                                        select *= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 25) {
                                        //시럽 라인
                                        selectX = 36;
                                        select *= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    }
                                } else if (ch == 'D') { // LEFT
                                    if (selectX == 14) {
                                        //샷 라인
                                        selectX = 4;
                                        select /= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 25) {
                                        //베이스 라인
                                        selectX = 14;
                                        select /= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    } else if (selectX == 36) {
                                        //시럽 라인
                                        selectX = 25;
                                        select /= 10;
                                        Console::drawCursor(selectX, selectY,
                                                            LIGHTGRAY, RED);
                                    }
                                }
                            }
                        }

                        if (ch == 'y') {
                            //커서 지우기
                            Console::drawCursor(4, 12, LIGHTGRAY, RED);

                            // 선택된 재료 글씨 지우기
                            for (int i = 10; i < showSelectY; i++) {
                                Console::gotoXY(50, i);
                                Console::setBackground(LIGHTGRAY);
                                Console::printColorString("            ");
                            }

                            // 현제 재조 중인 글씨 지우기
                            Console::gotoXY(26, 5);
                            Console::setBackground(LIGHTGRAY);
                            Console::printColorString("             ");
                            //선택된 재료 초기화
                            showSelectY = 10;
                            select = 1;
                            //좌표 초기화
                            selectX = 4;
                            selectY = 12;

                            //커피만들기
                            makeCoffee[i][j] = selectIngerdients;
                            break;
                        }

                        // 같은 종류 재료 중복 추가 불가!
                        if (select % 10 != 0) {
                            //샷 라인
                            if (selectIngerdients % 10 == 0) {
                                selectIngerdients += select;
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(selectX, selectY);
                                Console::drawCursor(selectX, selectY, LIGHTGRAY,
                                                    RED);
                            }
                        } else if (select % 100 != 0) {
                            //베이스 라인
                            if ((selectIngerdients % 100) / 10 == 0) {
                                selectIngerdients += select;
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(selectX, selectY);
                                Console::drawCursor(selectX, selectY, LIGHTGRAY,
                                                    RED);
                            }
                        } else if (select % 1000 != 0) {
                            //시럽 라인
                            if ((selectIngerdients % 1000) / 100 == 0) {
                                selectIngerdients += select;
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(selectX, selectY);
                                Console::drawCursor(selectX, selectY, LIGHTGRAY,
                                                    RED);
                            }
                        } else if (select % 10000 != 0) {
                            //재료 라인
                            if ((selectIngerdients % 10000) / 1000 == 0) {
                                selectIngerdients += select;
                                Console::gotoXY(50, showSelectY++);
                                Console::printColorString(inger[select].c_str(),
                                                          LIGHTMAGENTA);
                                Console::gotoXY(selectX, selectY);
                                Console::drawCursor(selectX, selectY, LIGHTGRAY,
                                                    RED);
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

            (successOrfail) ? page.workingPage3_day() : page.workingPage4_day();

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
Store::Store() {
    int cursor; // 커서값이 있다고 생각하자
    printItem(level);
}

//상점 품목 표시
//커서 첫 위치 조정해야함
int Store::printItem(int level) {
    menu1 = access(path_menu1, F_OK);
    menu2 = access(path_menu2, F_OK);
    menu3 = access(path_menu3, F_OK);
    menu4 = access(path_menu4, F_OK);

    if (menu1 == -1) { //구매기록없음
        if (level >= lev_menu1) {
            cout << "          1. 홍차" << endl;
        } else {
            cout << "[Locked]  1. 홍차 " << endl;
        }
    } else { // 구매기록 있음
        cout << " [Owned]  1. 홍차 " << endl;
    }
    cout << endl;

    if (menu2 == -1) { //구매기록없음
        if (level >= lev_menu2) {
            cout << "          2. 레몬 에이드" << endl;
        } else {
            cout << "[Locked]  2. 레몬 에이드 " << endl;
        }
    } else { // 구매기록 있음
        cout << " [Owned]  2. 레몬 에이드 " << endl;
    }
    cout << endl;

    if (menu3 == -1) { //구매기록없음
        if (level >= lev_menu3) {
            cout << "          3. 카페모카" << endl;
        } else {
            cout << "[Locked]  3. 카페모카 " << endl;
        }
    } else { // 구매기록 있음
        cout << " [Owned]  3. 카페모카 " << endl;
    }
    cout << endl;

    if (menu4 == -1) { //구매기록없음
        if (level >= lev_menu4) {
            cout << "          4. 카라멜 마키야또" << endl;
        } else {
            cout << "[Locked]  4. 카라멜 마키야또" << endl;
        }
    } else { // 구매기록 있음
        cout << " [Owned]  4. 카라멜 마키야또" << endl;
    }
    cout << endl;

    return 0;
}

int Store::buyItem(int cursor) {
    // 레시피를 소유하고 있지 않음
    switch (cursor) {
    case 1:
        if (level >= lev_menu1 && money >= cost_menu1) {
            cout << "해당 레시피를 구매하시겠습니까? 잔액에서" << cost_menu1
                 << "원이 차감됩니다." << endl;
            cout << "구매하시려면 Enter 자판을 눌러주세요. 아니라면  왼쪽 "
                    "방향키를 눌러주세요."
                 << endl;
            switch (cursor) {
                int fd = 0;

                // case 1//"Enter": //엔터키가 눌렸을 때 - 수정 필요
                //     fd = open(path_menu1, O_RDWR | O_CREAT);
                //     if (fd == -1) {
                //         perror("file open() error!");
                //         exit(-1);
                //     }
                //     close(fd);
                //     cout << "구매가 완료되었습니다." << endl;

                // case 2//"왼쪽": // 왼쪽 방향키가 눌렸을 때
                //     printItem(level);
            }
        } else {
            cout << "구매 조건이 충족되지 않았습니다. 상점 초기 화면으로 "
                    "돌아갑니다."
                 << endl;
            printItem(level);
        }
        break;
    case 2:
        if (level >= lev_menu2 && money >= cost_menu2) {
            cout << "해당 레시피를 구매하시겠습니까? 잔액에서" << cost_menu1
                 << "원이 차감됩니다." << endl;
            cout << "구매하시려면 Enter 자판을 눌러주세요. 아니라면 "
                    "방향키를 "
                    "눌러주세요."
                 << endl;
            switch (cursor) {
                int fd = 0;
                // case "Enter": //엔터키가 눌렸을 때
                //     fd = open(path_menu2, O_RDWR | O_CREAT);
                //     if (fd == -1) {
                //         perror("file open() error!");
                //         exit(-1);
                //     }
                //     close(fd);
                //     cout << "구매가 완료되었습니다." << endl;

                // case "왼쪽": // 왼쪽 방향키가 눌렸을 때
                //     printItem(level);
            }
        } else {
            cout << "구매 조건이 충족되지 않았습니다. 상점 초기 화면으로 "
                    "돌아갑니다."
                 << endl;
            printItem(level);
        }
        break;
    case 3:
        if (level >= lev_menu3 && money >= cost_menu3) {
            cout << "해당 레시피를 구매하시겠습니까? 잔액에서" << cost_menu1
                 << "원이 차감됩니다." << endl;
            cout << "구매하시려면 Enter 자판을 눌러주세요. 아니라면 "
                    "방향키를 "
                    "눌러주세요."
                 << endl;
            switch (cursor) {
                int fd = 0;
                // case "Enter": //엔터키가 눌렸을 때
                //     fd = open(path_menu3, O_RDWR | O_CREAT);
                //     if (fd == -1) {
                //         perror("file open() error!");
                //         exit(-1);
                //     }
                //     close(fd);
                //     cout << "구매가 완료되었습니다." << endl;

                // case "왼쪽": // 왼쪽 방향키가 눌렸을 때
                //     printItem(level);
            }
        } else {
            cout << "구매 조건이 충족되지 않았습니다. 상점 초기 화면으로 "
                    "돌아갑니다."
                 << endl;
            printItem(level);
        }
        break;
    case 4:
        if (level >= lev_menu3 && money >= cost_menu3) {
            cout << "해당 레시피를 구매하시겠습니까? 잔액에서" << cost_menu1
                 << "원이 차감됩니다." << endl;
            cout << "구매하시려면 Enter 자판을 눌러주세요. 아니라면 "
                    "방향키를 "
                    "눌러주세요."
                 << endl;
            switch (cursor) {
                int fd = 0;

                // case "Enter": //엔터키가 눌렸을 때
                //     fd = open(path_menu4, O_RDWR | O_CREAT);
                //     if (fd == -1) {
                //         perror("file open() error!");
                //         exit(-1);
                //     }
                //     close(fd);
                //     cout << "구매가 완료되었습니다." << endl;

                // case "왼쪽": // 왼쪽 방향키가 눌렸을 때
                //     printItem(level);
            }
        } else {
            cout << "구매 조건이 충족되지 않았습니다. 상점 초기 화면으로 "
                    "돌아갑니다."
                 << endl;
            printItem(level);
        }
        break;
    }

    // 샀다는 거 반환해야함 (벡터나 배열에 넣어주자) -> 깃허브 CafeTycoon에
    // 올라온 User 파일을 보았더니 recipe라는 벡터로 저장하는 것으로
    // 보였으나 왜 길이가 2이지,,? 라는 생각이 들어서 어떻게 쓰려고 만든
    // 벡터인지 모르겠음 다시 display 함수 호출해야하는지 첫화면으로
    // 돌아가는지 모르겠음
}

Minigame::Minigame() {

    int cursor;

    wantGame();
}
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
