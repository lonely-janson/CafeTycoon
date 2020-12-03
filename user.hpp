#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>
#include <vector>

using namespace std;

class Data {
  public:
    string username;
    string dataPath;

    Data();
    bool signUp(); //회원가입
    bool signIn(); //로그인
};

class User {
  private:
    string name;   // 사용자 이름
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
    int maxEx; // 습득해야하는 성취도
    int curEx; // 현제 성취도

  public:
    User(string _name); //임시
    // User(Data &data);
    User(User &user);
    string getName() { return name; }
    int getlevel() { return level; }
    int getMoney() { return money; }
    int getCountsell() { return countSell; }
    bool getRecipe(int index) { return recipe[index]; }
    int getCurEx() { return curEx; }
    int getMaxEx() { return maxEx; }

    int addEx(int ex); //레벨업 시 return 1, 그외 return 0
    void addMoney(int _money) { money += _money; }       //돈 획득
    void addCountsell(int count) { countSell += count; } //총 판매 커피 추가
};

#endif // __USER_HPP__
