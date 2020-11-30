#include "perform.hpp"
#include "console.hpp"
#include "user.hpp"
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
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
}

bool Data::signUp() {
    string id;
    string pw;
    string pwPath;

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
        // cout << i << endl;
        // 시간초 보여주는 함수 넣기;
    }
}

void Game::start(User &user) {
    int pid;
    key_t key;
    int id;
    Msg msg;
    size_t size = sizeof(msg) - sizeof(long);

    string checkShowRecipe;

    msg.type = 0;
    key = ftok("./main.cpp", 1);
    id = msgget(key, IPC_CREAT | 0600);

    pid = fork();
    if (pid == -1) {
        perror("fork() error!");
        return;
    } else if (pid == 0) {
        //게임 종료 후 데이터 저장

        msgrcv(id, &msg, size, msg.type, 0);
        cout << "0 : " << msg.data[0] << ", 1 : " << msg.data[1];
        user.addMoney(msg.data[0]);
        user.addCountsell(msg.data[1]);

    } else {
        //게임 진행
        map<int, int> orderd; // 커피 종류 및 수량 저장
        int numberOfType;     // 커피 종류 개수
        int kind;             // 커피 종류

        const vector<string> coffeeName = {"americano", "cafeLattee",
                                           "blackTea",  "cafeMocha",
                                           "lemonade",  "caramelMacchiato"};

        const vector<int> coffeePrice = {1000, 1500, 2000, 3000, 4000, 5000};
        const vector<int> recipe = {12, 32, 1010, 132, 3350, 5532};
        // 올바른 recipe 값
        // americano = 12,cafeLattee = 22, blackTea = 1010, cafeMocha = 122,
        // lemonade = 2250,caramelMacchiato = 5522
        const vector<vector<string>> ingerdients = {
            {"0", "1", "2"},
            {"water", "milk", "sparkling water"},
            {"mochaSyrup", "lemonSyrup", "caramelSyrup"},
            {"blackTeaBag", "ice", "caramelDrizzle"}};
        const double failPercnt = 0.8;

        map<int, int>::iterator iter;
        map<int, int>::iterator c_end;

        int selectIngerdients; //선택한 커피 재료 모음
        int select;            // 선택한 재료 저장

        vector<vector<int>> makeCoffee; //최종 제작 커피 저장 배열
        bool successOrfail;             // 성공 여부
        int totalPrice;                 // 획득한 돈
        int countSell;

        char ch; // 키보드 입력

        //난수 생성
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> randNumberOfType(1, user.getlevel() +
                                                              1); // 종류 개수
        uniform_int_distribution<int> randQuantity(1, 5); // 주문 개수
        uniform_int_distribution<int> randKindOfType(
            0,
            user.getlevel()); //커피 종류

        //타이머 설정
        // alarm(10);

        // 시간 보여주기
        pthread_t tid = 0;
        if (pthread_create(&tid, NULL, showTime, NULL)) {
            perror("pthread_creat() error!");
            exit(-1);
        }

        if (signal(SIGALRM, gameOver) == SIG_ERR) {
            perror("signal() error!");
        }

        // while () {
        numberOfType = randNumberOfType(gen);

        // 메뉴 주문
        for (int i = 0; i < numberOfType; i++) {
            kind = randKindOfType(gen);
            c_end = orderd.end();
            if (user.getRecipe(kind) && orderd.find(kind) == c_end) {
                orderd[kind] = randQuantity(gen);
            } else {
                i--;
            }
        }

        // ------ 디자인 변경 필요 -----
        //주문 정보 출력
        cout << numberOfType << endl;
        for (iter = orderd.begin(); iter != orderd.end(); iter++) {
            cout << "[" << coffeeName[iter->first] << ", " << iter->second
                 << "]" << endl;
        }

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
                    cout << "Cafe Mocha : mocha syrup, shot(2), milk " << endl;
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

        Console::linux_getch(); //입력 버퍼에 남아있는 엔터키 제거
        //배열 초기화

        makeCoffee = vector<vector<int>>(numberOfType, vector<int>(5));
        iter = orderd.begin();
        for (int i = 0; i < numberOfType && iter != orderd.end(); iter++, i++) {

            for (int j = 0; j < iter->second; j++) {

                selectIngerdients = 0;

                while (1) { // 커피 재료 선택
                    select = 1;
                    // 키보드 입력
                    while (1) { // 방향키 입력
                        cout << "select : " << select << endl;
                        ch = Console::linux_getch();
                        if (ch == ENTER) {
                            break;
                        } else if (ch == 'y') { // 커피 완성
                            break;
                        } else {
                            Console::linux_getch();
                            ch = Console::linux_getch();
                            if (ch == 'A') {
                                // UP
                                if (select / 1000 > 1) //재료 라인
                                    select -= 2000;
                                else if ((select % 1000) / 100 > 1) //시럽 라인
                                    select -= 200;
                                else if ((select % 100) / 10 > 1) //베이스 라인
                                    select -= 20;
                                else if ((select % 10) > 1) //샷 라인
                                    select -= 1;
                            } else if (ch == 'B') {
                                // DOWN
                                if (select / 10 == 0) {
                                    // 샷 라인
                                    if (select % 10 < 5) {
                                        select += 1;
                                    }
                                } else if (select / 100 == 0) {
                                    // 베이스 라인
                                    if (select % 100 < 50) {
                                        select += 20;
                                    }
                                } else if (select / 1000 == 0) {
                                    // 시럽 라인
                                    if (select % 1000 < 500) {
                                        select += 200;
                                    }
                                } else if (select % 10000 < 5000) {
                                    // 재료 라인
                                    select += 2000;
                                }
                            } else if (ch == 'C') { // RIGHT
                                if (select % 10 != 0) {
                                    //샷 라인
                                    select = 10;
                                } else if (select % 100 != 0) {
                                    //베이스 라인
                                    select = 100;
                                } else if (select % 1000 != 0) {
                                    //시럽 라인
                                    select = 1000;
                                }
                            } else if (ch == 'D') { // LEFT
                                if (select / 1000 != 0) {
                                    //재료 라인
                                    select = 100;
                                } else if (select / 100 != 0) {
                                    //시럽 라인
                                    select = 10;
                                } else if (select / 10 != 0) {
                                    //베이스 라인
                                    select = 1;
                                }
                            }
                        }
                    }

                    if (ch == 'y') {
                        //커피만들기
                        makeCoffee[i][j] = selectIngerdients;
                        //--------test-----------
                        cout << "selectIngerdients : " << selectIngerdients
                             << endl;
                        break;
                    }

                    // 같은 종류 재료 중복 추가 불가!
                    if (select % 10 != 0) {
                        //샷 라인
                        selectIngerdients +=
                            (selectIngerdients % 10 == 0) ? select : 0;
                    } else if (select % 100 != 0) {
                        //베이스 라인
                        selectIngerdients +=
                            ((selectIngerdients % 100) / 10 == 0) ? select : 0;
                    } else if (select % 1000 != 0) {
                        //시럽 라인
                        selectIngerdients +=
                            ((selectIngerdients % 1000) / 100 == 0) ? select
                                                                    : 0;
                    } else if (select % 10000 != 0) {
                        //재료 라인
                        selectIngerdients +=
                            ((selectIngerdients % 10000) / 1000 == 0) ? select
                                                                      : 0;
                    }

                    //--------test-----------
                    cout << "selectIngerdients : " << selectIngerdients << endl;
                }
            }
        }

        iter = orderd.begin();
        successOrfail = true;
        totalPrice = 0;
        countSell = 0;

        for (int i = 0; i < numberOfType && iter != orderd.end(); i++, iter++) {
            countSell += iter->second;
            for (int j = 0; j < iter->second; j++) {
                if (recipe[iter->first] != makeCoffee[i][j]) {
                    successOrfail = false;
                    cout << coffeeName[iter->first] << ": false" << endl;
                    totalPrice += coffeePrice[iter->first] * failPercnt;
                } else {
                    totalPrice += coffeePrice[iter->first];
                    cout << coffeeName[iter->first] << ": true" << endl;
                }
            }
        }

        //-----------test--------
        cout << "totalPrice : " << totalPrice << ", countSell : " << countSell
             << endl;
        msg.data[0] = totalPrice;
        msg.data[1] = countSell;

        msgsnd(id, &msg, size, 0); //데이터 저장 프로세스에게 데이터 전송
        while (1)
            sleep(1);
        //}
    }

    msgctl(id, IPC_RMID, NULL);
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
