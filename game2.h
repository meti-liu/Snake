#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
class RockPaperScissorsGame {
public:
    void play() {
        cout << "��ӭ����ʯͷ��������Ϸ����ѡ��1=ʯͷ��2=������3=������";
        int userChoice;
        cin >> userChoice;

        int computerChoice = rand() % 3 + 1;

        if (userChoice == computerChoice) {
            cout << "ƽ�֣�\n";
        } else if ((userChoice == 1 && computerChoice == 2) ||
                   (userChoice == 2 && computerChoice == 3) ||
                   (userChoice == 3 && computerChoice == 1)) {
            cout << "��Ӯ�ˣ�\n";
        } else {
            cout << "�����Ӯ�ˣ�\n";
        }
    }
};