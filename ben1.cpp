#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

std::string longestPalindrome(const std::string& s) {
    int n = s.size();
    if (n <= 1) return s;

    int maxLen = 1;
    int start = 0;
    std::vector<std::vector<bool>> dp(n, std::vector<bool>(n, false));

    // All substrings of length 1 are palindromes
    for (int i = 0; i < n; ++i) {
        dp[i][i] = true;
    }

    // Check for substrings of length 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            maxLen = 2;
            start = i;
        }
    }

    // Check for substrings of length greater than 2
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (len > maxLen) {
                    maxLen = len;
                    start = i;
                }
            }
        }
    }

    return s.substr(start, maxLen);
}

std::string get_random_string(int length) {
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    std::string result_str;
    result_str.reserve(length);

    for (int i = 0; i < length; ++i) {
        result_str += letters[rand() % letters.size()];
    }

    return result_str;
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed the random number generator
    std::string random_string = get_random_string(1000);
    std::string longest_palindrome = longestPalindrome(random_string);
    std::cout << "Longest Palindrome: " << longest_palindrome << std::endl;
    return 0;
}

