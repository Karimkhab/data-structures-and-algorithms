// Karim Khabibrakhmanov DSAI - 05

#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    int points;
    string name;
public:
    Student(int points, string name) {
        this->points = points;
        this->name = name;
    }

    int getPoints() const {
        return points;
    }

    const string &getName() const {
        return name;
    }
};

void swapStudents(Student& a, Student& b) {
    Student temp = a;
    a = b;
    b = temp;
}

void quickSort(vector<Student>& students, int start, int end) {
    if (start >= end) return;
    int pivot = students[end].getPoints();
    int i = start - 1;
    for (int j = start; j < end; ++j) {
        if (students[j].getPoints() < pivot) {
            swapStudents(students[++i], students[j]);
        }
    }
    swapStudents(students[i + 1], students[end]);
    int pivotIndex = i + 1;
    quickSort(students, start, pivotIndex - 1);
    quickSort(students, pivotIndex + 1, end);
}

bool isMedian(const vector<Student>& students, const Student& medianStudent) {
    int less = 0;
    int greater = 0;
    int medianPoints = medianStudent.getPoints();

    for (const Student& student : students) {
        if (student.getPoints() < medianPoints) {
            less++;
        } else if (student.getPoints() > medianPoints) {
            greater++;
        }
    }

    if (less <= (students.size() / 2) && greater <= (students.size() / 2)){
        return true;
    }else{
        return false;
    }
}

string findMedianName(int N, vector<Student> students) {
    if (students.size() <= 5) {
        quickSort(students, 0, students.size() - 1);
        if (students.size()%2==0){
            return students[students.size() / 2 - 1].getName();
        }else{
            return students[students.size() / 2].getName();

        }
    }
    vector<Student> medianOfStudents;
    for (int i = 0; i < students.size(); i += 5) {
        int end = i + 5;
        if (end>students.size()){
            end = students.size();
        }
        vector<Student> partStudents(students.begin() + i, students.begin() + end);
        quickSort(partStudents, 0, partStudents.size() - 1);
        if (partStudents.size()%2==0){
            medianOfStudents.push_back(partStudents[partStudents.size() / 2 - 1]);

        }else{
            medianOfStudents.push_back(partStudents[partStudents.size() / 2]);
        }
    }

    string medianOfMediansName = findMedianName(medianOfStudents.size(), medianOfStudents);

    Student* medianOfMedians = nullptr;
    for (Student& student : students) {
        if (student.getName() == medianOfMediansName) {
            medianOfMedians = &student;
            break;
        }
    }

    if (medianOfMedians && isMedian(students, *medianOfMedians)) {
        return medianOfMedians->getName();
    } else {
        quickSort(students, 0, students.size() - 1);
        if (students.size()%2==0){
            return students[students.size() / 2 - 1].getName();
        }else{
            return students[students.size() / 2].getName();

        }
    }
}

int main() {
    int N;
    cin >> N;
    vector<Student> studentsOrigin;
    int num;
    string name;
    for (int i = 0; i < N; i++) {
        cin >> num >> name;
        studentsOrigin.emplace_back(num, name);
    }

    cout << findMedianName(N, studentsOrigin) << "\n";
    return 0;
}