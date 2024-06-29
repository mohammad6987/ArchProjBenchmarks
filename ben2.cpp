#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

class Solution {
public:
    int rob(const std::vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return nums[0];
        }

        std::vector<int> dp(n, 0);

        dp[0] = nums[0];
        dp[1] = std::max(nums[0], nums[1]);

        for (int i = 2; i < n; ++i) {
            dp[i] = std::max(dp[i - 1], nums[i] + dp[i - 2]);
        }

        return dp[n - 1];
    }
};

int main() {
    std::vector<int> nums = {183, 219, 57, 193, 94, 233, 202, 154, 65, 240, 97, 234, 100, 249, 186, 66, 90, 238, 168, 128, 177, 235, 50, 81, 185, 165, 217, 207, 88, 80,
                             112, 78, 135, 62, 228, 247, 211, 2, 7, 9, 3, 1, 5, 240, 97, 234, 100, 249};

    std::srand(static_cast<unsigned>(std::time(0)));
    std::vector<int> nums2(5000);
    for (int i = 0; i < 5000; ++i) {
        nums2[i] = std::rand() % 651 + 50; // Random numbers between 50 and 700
    }

    nums.insert(nums.end(), nums2.begin(), nums2.end());

    Solution solution;
    int result = solution.rob(nums);
    std::cout << "Maximum amount robbed: " << result << std::endl;

    return 0;
}

