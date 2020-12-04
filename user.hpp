#ifndef __USER_HPP__
#define __USER_HPP__

#include <map>
#include <string>
#include <vector>

using namespace std;

class Data {
  public:
    string username;
    string dataPath;
    string idPath;

    Data();
    bool signUp(); //회원가입
    bool signIn(); //로그인
};

class User {
  private:
    string name; // temp
    Data data;

    int level;     // 레벨
    int money;     // 돈
    int countSell; // 판매 커피 수
    vector<bool> recipe = std::vector<bool>(6);
    // 보유 및 습득 가능 레시피
    // vector의 크기는 level + 1
    // vector의 크기로 습득 가능 레시피 판단
    // 해당 인덱스의 데이터로 레시피 보유 유무 판단
    // 0 : 아메리카노, 1 : 카페라떼, 2 : 홍차, 3 : 카페모카, 4 : 레몬 에이드, 5
    // : 카라멜 마끼아또
    map<int, int> maxEx = {{1, 120}, {2, 230}, {3, 400}, {4, 600}, {5, 1000}};
    int curEx; // 현재 성취도

  public:
    User(Data &_data);
    User(User &user);
    int getlevel() { return level; }
    int getMoney() { return money; }
    int getCountsell() { return countSell; }
    bool getRecipe(int index) { return recipe[index]; }
    int getCurEx() { return curEx; }
    string getName() { return data.username; }
    string getDataPath() { return data.dataPath; }
    string getIdPath() { return data.idPath; }

    void addEx(int ex);           //레벨업 시 return 1, 그외 return 0
    void addMoney(int _money);    //돈 획득
    void addCountsell(int count); //총 판매 커피 추가
    void addRecipe(int index);    //레시피구매
};

#endif // __USER_HPP__
