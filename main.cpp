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
        cout << "��ѡ����Ϸ��\n";
        cout << "1. ��������Ϸ\n";
        cout << "2. ʯͷ��������Ϸ\n";
        cout << "3. �˳�\n";
        cin >> choice;

        switch (choice) {
            case 1:
                guessGame.play();
                break;
            case 2:
                snakegame.play();
                break;
            case 3:
                cout << "�ټ���\n";
                return 0;
            default:
                cout << "��Ч��ѡ��������ѡ��\n";
        }
    }

    return 0;
}