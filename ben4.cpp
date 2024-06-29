#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to perform convolution
void convolve(const std::vector<std::vector<int>>& matrix,
              std::vector<std::vector<int>>& result,
              const std::vector<std::vector<int>>& kernel) {
    int kernel_size = kernel.size();
    int offset = kernel_size / 2;
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = offset; i < rows - offset; ++i) {
        for (int j = offset; j < cols - offset; ++j) {
            int sum = 0;
            for (int m = 0; m < kernel_size; ++m) {
                for (int n = 0; n < kernel_size; ++n) {
                    int x = i + m - offset;
                    int y = j + n - offset;
                    sum += matrix[x][y] * kernel[m][n];
                }
            }
            result[i][j] = sum;
        }
    }
}

// Function to generate a 300x300 matrix with random values
std::vector<std::vector<int>> generate_matrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 255 + 1; // Random values between 1 and 255
        }
    }
    return matrix;
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed the random number generator

    // Generate a 300x300 non-zero matrix
    std::vector<std::vector<int>> matrix = generate_matrix(200, 200);

    // Define the convolution kernel
    std::vector<std::vector<int>> kernel = {
        {-1, -1, -1},
        {-1, 8, -1},
        {-1, -1, -1}
    };

    // Prepare the result matrix
    std::vector<std::vector<int>> result(200, std::vector<int>(200, 0));

    // Perform the convolution
    convolve(matrix, result, kernel);

    // Optional: Print the original and the result matrices
    // for (int i = 0; i < 300; ++i) {
    //     for (int j = 0; j < 300; ++j) {
    //         std::cout << result[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}


