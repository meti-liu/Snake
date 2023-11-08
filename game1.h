#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;  // 使用using指令

// 猜数字游戏类
class GuessNumberGame {
public:
    void play() {
        int numberToGuess = rand() % 100 + 1;
        int guess;
        int attempts = 0;

        cout << "欢迎来到猜数字游戏！我已经想好了一个1到100之间的数字。\n";

        while (true) {
            cout << "请输入你的猜测：";
            cin >> guess;
            attempts++;

            if (guess < numberToGuess) {
                cout << "太小了，请再试一次。\n";
            } else if (guess > numberToGuess) {
                cout << "太大了，请再试一次。\n";
            } else {
                cout << "恭喜你，你猜对了！你用了 " << attempts << " 次尝试。\n";
                break;
            }
        }
    }
};