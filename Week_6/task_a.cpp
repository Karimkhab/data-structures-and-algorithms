// Karim Khabibrakhmanov DSAI - 05
#include <iostream>
#include <vector>

using namespace std;

class Number{
public:
    int value;
    int id;
    int count;
    Number(int value,int id, int count): value(value),id(id), count(count){}
};

template<typename T>
vector<T> countingSort(vector<T>& arr, int minValue, int maxValue) {
    int range = maxValue - minValue + 1;
    vector<int> countForValue(range, 0);
    vector<T> arr1(arr.size(), T(0, 0,0));
    vector<T> result(arr.size(), T(0, 0,0));

    for (int i = 0; i < arr.size(); i++) {
        countForValue[arr[i].value - minValue]++;
    }

    for (int i = 0; i < arr.size(); i++) {
        arr[i].count = countForValue[arr[i].value - minValue];
    }

    int minCount = INT_MAX, maxCount = INT_MIN;
    for (int i = 0; i < countForValue.size(); i++) {
        if (countForValue[i] < minCount && countForValue[i] != 0) {
            minCount = countForValue[i];
        }
        if (countForValue[i] > maxCount && countForValue[i] != 0) {
            maxCount = countForValue[i];
        }
        if (i > 0) {
            countForValue[i] += countForValue[i - 1];
        }
    }

    int rangeForCount = maxCount - minCount + 1;

    for (int i = arr.size() - 1; i >= 0; i--) {
        int id = countForValue[arr[i].value - minValue] - 1;
        arr1[id] = arr[i];
        countForValue[arr[i].value - minValue]--;
    }

    vector<int> countForCount(rangeForCount, 0);
    for (int i = 0; i < arr1.size(); i++) {
        countForCount[arr1[i].count - minCount]++;
    }

    for (int i = 1; i < countForCount.size(); i++) {
        countForCount[i] += countForCount[i - 1];
    }

    for (int i = arr1.size() - 1; i >= 0; i--) {
        int id = countForCount[arr1[i].count - minCount] - 1;
        result[id] = arr1[i];
        countForCount[arr1[i].count - minCount]--;
    }

    return result;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int N;
    cin>>N;
    vector<Number> numbers;
    for (int i=0;i<N;i++){
        int value;
        cin>>value;
        numbers.push_back(Number(value,i,0));
    }
    int min=10*100,max = -10*100;
    for (int i=0;i<N;i++){
        if (numbers[i].value>max){
            max = numbers[i].value;
        }
        if (numbers[i].value<min){
            min = numbers[i].value;
        }
    }
    numbers = countingSort(numbers,min,max);
    for (int i=0;i<N;i++){
        cout<<numbers[i].value<<" "<<numbers[i].id<<"\n";
    }
    return 0;
}