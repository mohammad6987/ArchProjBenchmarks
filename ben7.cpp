// matrix_multiplication_benchmark.cpp
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using Matrix = std::vector<std::vector<int>>;

Matrix generateMatrix(int size) {
    Matrix matrix(size, std::vector<int>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = std::rand() % 100; // Random numbers between 0 and 99
        }
    }
    return matrix;
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    int size = A.size();
    Matrix C(size, std::vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

int main() {
    const int size = 50; // Size of the matrix

    // Seed for random number generation
    std::srand(std::time(nullptr));

    // Generate random matrices
    Matrix A = generateMatrix(size);
    Matrix B = generateMatrix(size);

    // Measure time for matrix multiplication
    clock_t start = clock();
    Matrix C = multiplyMatrices(A, B);
    clock_t end = clock();

    // Print execution time (can be disabled for benchmarks without output)
    // std::cout << "Matrix multiplication time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds." << std::endl;

    return 0;
}

