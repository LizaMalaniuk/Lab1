#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
const int N = 500;

vector<vector<int>> generateMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

vector<vector<int>> computeMatrixSequential(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    int k)
{
    int size = A.size();
    vector<vector<int>> C(size, vector<int>(size));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + k * B[i][j];
        }
    }
    return C;
}

int main() {

    return 0;
}
