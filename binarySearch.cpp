#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
int binary_search(const std::vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void measure_performance() {
    int n = 1000000;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000000;
    }
    std::sort(arr.begin(), arr.end());

    int best_case_target = arr[n / 2];
    auto start = std::chrono::high_resolution_clock::now();
    binary_search(arr, best_case_target);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> best_case_time = end - start;

    int worst_case_target = -1;
    start = std::chrono::high_resolution_clock::now();
    binary_search(arr, worst_case_target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> worst_case_time = end - start;

    int avg_case_target = arr[rand() % n];
    start = std::chrono::high_resolution_clock::now();
    binary_search(arr, avg_case_target);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> avg_case_time = end - start;

    std::cout << "Best case time: " << best_case_time.count() << " seconds" << std::endl;
    std::cout << "Worst case time: " << worst_case_time.count() << " seconds" << std::endl;
    std::cout << "Average case time: " << avg_case_time.count() << " seconds" << std::endl;
}

int main() {
    srand(time(0));
    measure_performance();
    return 0;
}