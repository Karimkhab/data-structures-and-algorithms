// Karim Khabibrakhmanov DSAI-05
#include <iostream>
#include <vector>


using namespace std;

vector<int> chipWayForMatrix(int N,int M,vector<vector<int>> matrix){
    vector<vector<int>> matrixSecond(N, vector<int>(M));
    matrixSecond[0][0] = matrix[0][0];
    for (int i = 1;i<M;i++){
        matrixSecond[0][i] = matrix[0][i] + matrixSecond[0][i-1];
    }
    for (int i = 1;i<N;i++){
        matrixSecond[i][0] = matrix[i][0] + matrixSecond[i-1][0];
    }
    for (int i=1;i<N;i++){
        for (int j=1;j<M;j++){
            matrixSecond[i][j] = min(matrixSecond[i-1][j],matrixSecond[i][j-1]) + matrix[i][j];
        }
    }

    vector<int> result;
    int row = N-1, column = M-1;
    while (row > 0 || column > 0) {
        result.push_back(matrix[row][column]);
        if (row == 0) {
            column--;
        } else if (column == 0) {
            row--;
        } else if (matrixSecond[row - 1][column] < matrixSecond[row][column - 1]) {
            row--;
        } else {
            column--;
        }
    }
    result.push_back(matrix[0][0]);
    cout<<matrixSecond[N-1][M-1]<<"\n";
    return result;
}


int main(){
    int N, M;
    cin>> N >> M;

    vector<vector<int>> matrix(N, vector<int>(M));
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            cin>>matrix[i][j];
        }
    }
    vector<int> resultArr = chipWayForMatrix(N,M,matrix);
    for (int i=resultArr.size()-1;i>-1;i--){
        cout<<resultArr[i]<<" ";
    }
}