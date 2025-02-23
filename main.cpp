#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

vector<vector<int>> generateMatrix(int size) {
    vector<vector<int>> matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

int main() {

    return 0;
}
