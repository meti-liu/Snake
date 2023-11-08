#include "game1.h"
#include "game2.h"
#include "game3.h"
#include<ctime>
using namespace std;
int main() {
    // srand(static_cast<unsigned>(time(nullptr)));

    GuessNumberGame guessGame;
    RockPaperScissorsGame rpsGame;
    game3 snakegame;

    int choice;
    while (true) {
        cout << "请选择游戏：\n";
        cout << "1. 猜数字游戏\n";
        cout << "2. 石头剪刀布游戏\n";
        cout << "3. 退出\n";
        cin >> choice;

        switch (choice) {
            case 1:
                guessGame.play();
                break;
            case 2:
                snakegame.play();
                break;
            case 3:
                cout << "再见！\n";
                return 0;
            default:
                cout << "无效的选择，请重新选择。\n";
        }
    }

    return 0;
}