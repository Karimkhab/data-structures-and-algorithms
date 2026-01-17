// Karim Khabibrakhmanov DSAI-05
#include <iostream>
#include <vector>

using namespace std;

static int N;

class JobTime {
public:
    int start;
    int end;
    int cost;
};

void swap(JobTime& a, JobTime& b) {
    JobTime temp = a;
    a = b;
    b = temp;
}

void quickSort(vector<JobTime>& jobs, int left, int right) {
    if (left >= right) return;
    int i = left, j = right;
    JobTime pivot = jobs[(left + right) / 2];
    while (i <= j) {
        while (jobs[i].end < pivot.end) i++;
        while (jobs[j].end > pivot.end) j--;

        if (i <= j) {
            swap(jobs[i], jobs[j]);
            i++;
            j--;
        }
    }
    quickSort(jobs, left, j);
    quickSort(jobs, i, right);
}

int maxCostOfJob(const vector<JobTime>& jobs, vector<int>& maxValueForItem, int point) {
    if (point < 0){
        return 0;
    }
    if (maxValueForItem[point] != -1){
        return maxValueForItem[point];
    }
    int nextId = -1;
    for (int i = point - 1; i >= 0; i--) {
        if (jobs[i].end <= jobs[point].start) {
            nextId = i;
            break;
        }
    }
    if (nextId != -1) {
        maxValueForItem[point] = max(jobs[point].cost + maxCostOfJob(jobs, maxValueForItem, nextId),maxCostOfJob(jobs, maxValueForItem, point - 1));
    }else{
        maxValueForItem[point] = max(jobs[point].cost ,maxCostOfJob(jobs, maxValueForItem, point - 1));
    }
    return maxValueForItem[point];
}

int main() {
    cin >> N;
    vector<JobTime> jobs(N);
    vector<int> maxValueForItem(N, -1);
    for (int i = 0; i < N; i++) {
        cin >> jobs[i].start;
    }
    for (int i = 0; i < N; i++) {
        cin >> jobs[i].end;
    }
    for (int i = 0; i < N; i++) {
        cin >> jobs[i].cost;
    }
    quickSort(jobs, 0, N - 1);
    cout << maxCostOfJob(jobs, maxValueForItem, N - 1);
    return 0;
}