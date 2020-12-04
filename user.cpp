#include "user.hpp"
#include "console.hpp"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <pwd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define PERMS 0755
#define BUF_SIZE 1

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
        if (mkdir(dataPath.c_str(), PERMS) == -1) {
            perror("mkdir() error!");
            exit(-2);
        }
    }
}

bool Data::signUp() {
    string id;
    string pw;
    string checkPw;
    string userSell;
    string userRanking;
    string userLevel;

    string pwPath;
    string levelPath;
    string moneyPath;
    string sellPath;
    string recipePath;
    string exPath;
    char *temp;

    int fd = 0;
    ssize_t wsize;
    char ch;
    struct stat fileinfo;

    while (1) {
        Console::gotoXY(15, 13);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("ID       :            ", CYAN);

        Console::gotoXY(27, 13);
        Console::setBackground(LIGHTGRAY);
        id = dataPath;
        id += Console::input();

        if (mkdir(id.c_str(), PERMS) == -1) {

            Console::gotoXY(15, 14);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("?? ???? ??????.", BLACK);
            Console::gotoXY(15, 15);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("????? ENTER? ?????", BLACK);
            Console::gotoXY(15, 16);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("?????? ESC? ?????.", BLACK);
            while (1) {
                ch = Console::linux_getch();
                if (ch == ENTER) {
                    break;
                } else if (ch == ESC) {
                    return false;
                }
            }
            Console::gotoXY(15, 14);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                           ", BLACK);
            Console::gotoXY(15, 15);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                                     ",
                                      BLACK);
            Console::gotoXY(15, 16);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                                 ",
                                      BLACK);

        } else {
            break;
        }
    }

    pw = "";
    checkPw = "";
    while (1) {
        // password first
        Console::gotoXY(15, 15);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("PW       :            ", MAGENTA);

        Console::gotoXY(27, 15);
        Console::setBackground(LIGHTGRAY);
        pw = Console::input(1);
        pwPath = id + "/pw.txt";

        fd = open(pwPath.c_str(), O_CREAT | O_WRONLY, PERMS);
        if (fd == -1) {
            perror("open() error!");
            rmdir(id.c_str());
            return false;
        }

        wsize = write(fd, (char *)pw.c_str(), pw.length());

        close(fd);

        if (wsize == -1) {
            perror("write() error!");
            remove(pwPath.c_str());
            rmdir(id.c_str());
            return false;
        }

        // pw retry
        fd = open(pwPath.c_str(), O_RDONLY);

        if (fd == -1) {
            perror("open() error!");
            return false;
        }

        if (fstat(fd, &fileinfo) == -1) {
            perror("fstat() error!");
            return false;
        }

        temp = (char *)malloc(fileinfo.st_size);
        if (read(fd, (char *)temp, fileinfo.st_size) == -1) {
            perror("read() error!");
            return false;
        }
        close(fd);

        Console::gotoXY(15, 17);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("PW AGAIN     :            ", LIGHTRED);

        Console::gotoXY(31, 17);
        Console::setBackground(LIGHTGRAY);
        checkPw = Console::input(1);
        checkPw = temp;

        if (checkPw == pw)
            break;
        else {
            Console::gotoXY(15, 16);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("?? ???????", BLACK);
            Console::gotoXY(15, 17);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("????? ENTER? ?????", BLACK);
            Console::gotoXY(15, 18);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("?????? ESC? ?????.", BLACK);
            while (1) {
                ch = Console::linux_getch();
                if (ch == ENTER) {
                    break;
                } else if (ch == ESC) {
                    remove(pwPath.c_str());
                    rmdir(id.c_str());
                    return false;
                }
            }
            Console::gotoXY(15, 16);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                           ", BLACK);
            Console::gotoXY(15, 17);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                                     ",
                                      BLACK);
            Console::gotoXY(15, 18);
            Console::setBackground(LIGHTGRAY);
            Console::printColorString("                                 ",
                                      BLACK);
        }
    }

    levelPath = id + "/level.txt";
    fd = open(levelPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "1", strlen("1"));

    close(fd);

    moneyPath = id + "/money.txt";
    fd = open(moneyPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    sellPath = id + "/sell.txt";
    fd = open(sellPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    recipePath = id + "/recipe.txt";
    fd = open(recipePath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "110000", strlen("110000"));

    close(fd);

    exPath = id + "/ex.txt";
    fd = open(exPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    Console::gotoXY(27, 21);
    Console::setBackground(LIGHTGRAY);
    Console::printColorString(">", RED);

    while (Console::linux_getch() != ENTER)
        ;

    return true;
}

bool Data::signIn() {
    string pw;
    string originPw;
    string pwPath;
    char *temp;
    int pwCount = 0;
    int idCount = 0;

    int fd = 0;
    struct stat fileinfo;

    while (1) {
        if (idCount++ > 5)
            return false;

        Console::gotoXY(30, 10);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("                    ");
        Console::gotoXY(30, 10);
        Console::setBackground(LIGHTGRAY);

        username = Console::input();
        idPath = dataPath + username;

        if (access(idPath.c_str(), F_OK) != -1) {
            break;
        }
    }

    pwPath = idPath + "/pw.txt";
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

    while (1) {
        if (pwCount++ > 5)
            return false;

        Console::gotoXY(30, 16);
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("                    ");
        Console::gotoXY(30, 16);
        Console::setBackground(LIGHTGRAY);

        pw = Console::input(1);

        if (pw == originPw) {
            break;
        }
    }

    return true;
}

User::User(Data &_data) {
    string levelPath = "";
    string moneyPath = "";
    string sellPath = "";
    string recipePath = "";
    string exPath = "";

    string _money = "";
    string _sell = "";
    string _ex = "";

    char temp[BUF_SIZE + 1];
    int i = 0;

    data = _data;

    int fd;
    ssize_t rsize;

    levelPath = data.idPath + "/level.txt";
    fd = open(levelPath.c_str(), O_RDONLY);

    memset(temp, '\0', BUF_SIZE + 1);
    rsize = read(fd, (char *)temp, BUF_SIZE);
    level = atoi(temp);

    close(fd);

    moneyPath = data.idPath + "/money.txt";
    fd = open(moneyPath.c_str(), O_RDONLY);
    if (fd == -1) {
        Console::setBackground(LIGHTGRAY);
        Console::printColorString("error", BLACK);
        Console::linux_getch();
    }

    do {
        memset(temp, '\0', BUF_SIZE + 1);
        rsize = read(fd, (char *)temp, BUF_SIZE);

        _money += temp;
    } while (rsize > 0);
    close(fd);

    money = stoi(_money);

    sellPath = data.idPath + "/sell.txt";
    fd = open(sellPath.c_str(), O_RDONLY);

    do {
        memset(temp, '\0', BUF_SIZE + 1);
        rsize = read(fd, (char *)temp, BUF_SIZE);

        _sell += temp;
    } while (rsize > 0);

    close(fd);

    countSell = stoi(_sell);

    recipePath = data.idPath + "/recipe.txt";
    fd = open(recipePath.c_str(), O_RDONLY);
    i = 0;
    do {
        memset(temp, '\0', BUF_SIZE + 1);
        rsize = read(fd, (char *)temp, BUF_SIZE);
        if (rsize < 0)
            break;
        recipe[i++] = (strcmp(temp, "0") == 0) ? false : true;
    } while (rsize > 0);

    close(fd);

    exPath = data.idPath + "/ex.txt";
    fd = open(exPath.c_str(), O_RDONLY);
    do {
        memset(temp, '\0', BUF_SIZE + 1);
        rsize = read(fd, (char *)temp, BUF_SIZE);
        if (rsize < 0)
            break;
        _ex += temp;
    } while (rsize > 0);
    close(fd);

    curEx = stoi(_ex);
}

User::User(User &user) {
    data = user.data;
    level = user.level;
    money = user.money;
    countSell = user.countSell;
    recipe.clear();
    recipe.assign(user.recipe.begin(), user.recipe.end());
    curEx = user.curEx;
}

void User::addEx(int ex) {
    curEx += ex;

    string exPath = data.idPath + "/ex.txt";
    string lvPath = data.idPath + "/level.txt";

    char strEx[4];
    int fd;

    if (curEx >= maxEx[level]) {

        char temp;

        level++;

        fd = open(lvPath.c_str(), O_WRONLY | O_TRUNC);
        temp = level + '0';
        write(fd, &temp, sizeof(temp));

        curEx -= maxEx[level - 1];

        close(fd);
    }

    memset(strEx, '\0', sizeof(strEx));
    fd = open(exPath.c_str(), O_WRONLY | O_TRUNC);
    write(fd, strEx, strlen(strEx));
    close(fd);
}

void User::addMoney(int _money) {
    string moneyPath = data.idPath + "/money.txt";
    char strMoney[8];

    money += _money;

    memset(strMoney, '\0', sizeof(strMoney));
    sprintf(strMoney, "%d", money);
    int fd = open(moneyPath.c_str(), O_WRONLY | O_TRUNC);

    write(fd, strMoney, strlen(strMoney));
    close(fd);
}

void User::addCountsell(int count) {
    string sellPath = data.idPath + "/sell.txt";
    char strSell[4];

    countSell += count;

    memset(strSell, '\0', sizeof(strSell));
    sprintf(strSell, "%d", countSell);
    int fd = open(sellPath.c_str(), O_WRONLY | O_TRUNC);

    write(fd, strSell, strlen(strSell));
    close(fd);
}

void User::addRecipe(int index) {
    ssize_t wsize;
    string recipePath = data.idPath + "/recipe.txt";
    int fd = open(recipePath.c_str(), O_WRONLY | O_TRUNC);
    recipe[index] = true;

    char temp[6];
    for (int i = 0; i < 6; i++) {
        temp[i] = (recipe[i]) ? '1' : '0';
    }
    wsize = write(fd, temp, sizeof(temp));
    close(fd);
}
