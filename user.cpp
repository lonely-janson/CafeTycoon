#include "user.hpp"
#include "console.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <iostream>
#include <pwd.h>

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
        //??? ???? ???;
        if (mkdir(dataPath.c_str(), PERMS) == -1) {
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
    string levelPath;
    string moneyPath;
    string sellPath;
    string recipePath;
    string exPath;

    int fd = 0;
    ssize_t wsize;

    // ??? ??
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

    // ???? ??
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

    //??? ?? ??
    levelPath = dataPath + "/level.txt";
    fd = open(levelPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "1", strlen("1"));

    close(fd);

    moneyPath = dataPath + "/money.txt";
    fd = open(moneyPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    sellPath = dataPath + "/sell.txt";
    fd = open(sellPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    recipePath = dataPath + "/recipe.txt";
    fd = open(recipePath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);

    exPath = dataPath + "/ex.txt";
    fd = open(exPath.c_str(), O_CREAT | O_WRONLY, PERMS);
    wsize = write(fd, "0", strlen("0"));

    close(fd);



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

    // ??? ??
    while (1) {
        if (idCount++ > 5)
            return false;
        cout << "ID : ";
        id = dataPath;
        id += Console::input();

        if (access(dataPath.c_str(), F_OK) != -1) {
            //??? ????
            break;
        }
    }

    //???? ????;

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

    //???? ??
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

User::User(string _name) {
    name = _name;
    level = 10; // "?? ??"
    money = 66000;
    countSell = 0;
    recipe.assign(2, true);
    maxEx = 100;
    curEx = 1;
}

User::User(User &user) {
    name = user.name;
    level = user.level;
    money = user.money;
    countSell = user.countSell;
    recipe.clear();
    recipe.assign(user.recipe.begin(), user.recipe.end());
    maxEx = user.maxEx;
    curEx = user.curEx;
}

int User::addEx(int ex) {
    curEx += ex;

    if (curEx >= maxEx) {
        level++;
        curEx -= maxEx;
        maxEx *= 2;
        return 1;
    }

    return 0;
}
