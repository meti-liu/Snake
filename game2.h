#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class RockPaperScissorsGame {
public:
    void play() {
        cout << "欢迎来到石头剪刀布游戏！请选择（1=石头，2=剪刀，3=布）：";
        int userChoice;
        cin >> userChoice;

        int computerChoice = rand() % 3 + 1;

        if (userChoice == computerChoice) {
            cout << "平局！\n";
        } else if ((userChoice == 1 && computerChoice == 2) ||
                   (userChoice == 2 && computerChoice == 3) ||
                   (userChoice == 3 && computerChoice == 1)) {
            cout << "你赢了！\n";
        } else {
            cout << "计算机赢了！\n";
        }
    }
};