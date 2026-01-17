// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class Coordinate {
public:
    double x;
    double y;
    double distance;
    Coordinate(double x, double y) : x(x), y(y) {}
    double distanceCompute() {
        this->distance = sqrt(x * x + y * y);
        return this->distance;
    }
};

bool cmpr(const Coordinate &a, const Coordinate &b) {
    return a.distance < b.distance;
}

template <typename T>
void insertionSort(vector<T>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && cmpr(key, arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

double getDistance(const Coordinate& coord) {
    return coord.distance;
}

template <typename T>
vector<T> bucketSort(vector<T>& arr, double (*getDistance)(const T&)) {
    vector<vector<T>> buck(arr.size());

    for (int i = 0; i < arr.size(); i++) {
        double distance = getDistance(arr[i]);
        int bi = static_cast<int>(floor(arr.size() * distance));
        if (bi >= arr.size()) {
            bi = arr.size() - 1;
        }
        buck[bi].push_back(arr[i]);
    }

    for (int i = 0; i < buck.size(); i++) {
        insertionSort(buck[i]);
    }

    int index = 0;
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < buck[i].size(); j++) {
            arr[index++] = buck[i][j];
        }
    }

    return arr;
}

int main() {
    int amountOfCoord;
    cin >> amountOfCoord;
    vector<Coordinate> coordinates(amountOfCoord, Coordinate(0, 0));
    for (int i = 0; i < amountOfCoord; i++) {
        cin >> coordinates[i].x >> coordinates[i].y;
        coordinates[i].distanceCompute();
    }

    coordinates = bucketSort(coordinates, getDistance);

    for (int i = 0; i < amountOfCoord; i++) {
        cout << fixed << setprecision(4) << coordinates[i].x << " " << coordinates[i].y << "\n";
    }

    return 0;
}