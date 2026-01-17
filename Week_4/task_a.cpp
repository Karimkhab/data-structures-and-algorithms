// Karim Khabibrakhmanov DSAI - 05

#include <iostream>
using namespace std;

int xArraySearch(int Start, int End, int K, int arrayNum[], int x) {
    if (Start > End) {
        return -1;
    }

    if (Start == End) {
        if (arrayNum[Start] == x) {
            return Start;
        } else {
            return -1;
        }
    }

    int size = End - Start + 1;
    int step = size / K;
    if (size % K != 0) {
        step++;
    }

    int midPoints[K + 1];
    midPoints[0] = Start;
    for (int i = 1; i <= K; i++) {
        midPoints[i] = Start + i * step;
        if (midPoints[i] > End) {
            midPoints[i] = End;
        }
    }
    for (int i = 0; i < K; i++) {
        if (x == arrayNum[midPoints[i]]) {
            return midPoints[i];
        } else if (x < arrayNum[midPoints[i]]) {
            if (i == 0) {
                return xArraySearch(Start, midPoints[i] - 1, K, arrayNum, x);
            }
            return xArraySearch(midPoints[i - 1] + 1, midPoints[i] - 1, K, arrayNum, x);
        }
    }

    return xArraySearch(midPoints[K - 1] + 1, End, K, arrayNum, x);
}

int main() {
    int N, K, M;
    cin >> N >> K;
    int arrayNum[N];

    for (int i = 0; i < N; i++) {
        cin >> arrayNum[i];
    }
    cin >> M;
    int arrayForX[M];
    for (int i = 0; i < M; i++) {
        cin >> arrayForX[i];
    }

    for (int i = 0; i < M; i++) {
        cout << xArraySearch(0, N - 1, K, arrayNum, arrayForX[i]) << "\n";
    }

    return 0;
}