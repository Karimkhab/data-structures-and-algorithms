//Karim Khabibrakhmanov DSAI-05

#include <iostream>
using namespace std;

int countPlayers,countLiders;

typedef struct {
    string name;
    int score;
}Player;

void selectionSort(Player* players) {
    for (int i = 0; i < countLiders + 1; i++) {
        int maxIndex = i;
        for (int j = i; j < countPlayers; j++) {
            if (players[j].score > players[maxIndex].score) {
                maxIndex = j;
            }
        }
        if (maxIndex != i) {
            swap(players[i], players[maxIndex]);
        }
    }
}

int main() {
    cin >> countPlayers >> countLiders;
    if (countLiders > countPlayers) {
        countLiders = countPlayers;
    }
    Player players[countPlayers];

    for(int i=0;i<countPlayers;i++) {
        cin >> players[i].name >> players[i].score;
    }

    selectionSort(players);
    for(int i=0;i<countLiders;i++) {
        cout << players[i].name << " " << players[i].score << endl;
    }
}