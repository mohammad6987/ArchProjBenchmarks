#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

void bubble_sort(std::vector<int>& array) {
    int size = array.size();
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (array[i] > array[j]) {
                std::swap(array[i], array[j]);
            }
        }
    }
}

std::vector<int> generate_array(int n) {
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        nums[i] = std::rand() % 200 + 1; // Random numbers between 1 and 200
    }
    return nums;
}

int main() {
    std::srand(static_cast<unsigned>(std::time(0))); // Seed the random number generator

    std::vector<int> array = generate_array(1000);
    bubble_sort(array);

    // Optional: Print the sorted array (commented out for performance reasons)
    // for (int num : array) {
    //     std::cout << num << " ";
    // }
    // std::cout << std::endl;

    return 0;
}

