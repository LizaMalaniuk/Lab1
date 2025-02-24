#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <thread>

using namespace std;
const int N = 5000;
const int THREADS = 192;

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

// Функція для обчислення частини матриці у потоці
void computePart(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    vector<vector<int>>& C,
    int k, int startRow, int endRow)
{
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + k * B[i][j];
        }
    }
}

int main() {
    srand(time(0));
    int k = 5;


    auto A = generateMatrix(N);
    auto B = generateMatrix(N);
    vector<vector<int>> C_parallel(N, vector<int>(N));

    // Послідовне обчислення
    auto start_seq = chrono::high_resolution_clock::now();
    auto C_seq = computeMatrixSequential(A, B, k);
    auto stop_seq = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seq = stop_seq - start_seq;

    cout << "Execution time (without parallelization): " << elapsed_seq.count() << " seconds" << endl;

    //  Паралельне обчислення
    auto start_par = chrono::high_resolution_clock::now();
    vector<thread> threads;
    int rowsPerThread = N / THREADS;

    for (int i = 0; i < THREADS; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == THREADS - 1) ? N : (i + 1) * rowsPerThread;
        threads.emplace_back(computePart, cref(A), cref(B), ref(C_parallel), k, startRow, endRow);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    auto stop_par = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_par = stop_par - start_par;

    cout << "Execution time (with parallelization): " << elapsed_par.count() << " seconds" << endl;

    return 0;
}
