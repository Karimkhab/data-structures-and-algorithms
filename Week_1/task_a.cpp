//Karim Khabibrakhmanov DSAI-05

#include <iostream>
using namespace std;

void sort(int* arr, int n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[i - 1]) {
                swap(arr[i], arr[i - 1]);
                swapped = true;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for(int i=0;i<n;i++) {
        cin >> arr[i];
    }

    sort(arr,n);
    for(int i=0;i<n;i++) {
        cout << arr[i] << " ";
    }
}