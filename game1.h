#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;  // ʹ��usingָ��

// ��������Ϸ��
class GuessNumberGame {
public:
    void play() {
        int numberToGuess = rand() % 100 + 1;
        int guess;
        int attempts = 0;

        cout << "��ӭ������������Ϸ�����Ѿ������һ��1��100֮������֡�\n";

        while (true) {
            cout << "��������Ĳ²⣺";
            cin >> guess;
            attempts++;

            if (guess < numberToGuess) {
                cout << "̫С�ˣ�������һ�Ρ�\n";
            } else if (guess > numberToGuess) {
                cout << "̫���ˣ�������һ�Ρ�\n";
            } else {
                cout << "��ϲ�㣬��¶��ˣ������� " << attempts << " �γ��ԡ�\n";
                break;
            }
        }
    }
};