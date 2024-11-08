import time
import random

def binary_search(arr, target):
    low, high = 0, len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def measure_performance():
    n = 1000000
    arr = sorted([random.randint(1, 1000000) for _ in range(n)])

    best_case_target = arr[n // 2]
    start = time.time()
    binary_search(arr, best_case_target)
    best_case_time = time.time() - start

    worst_case_target = -1
    start = time.time()
    binary_search(arr, worst_case_target)
    worst_case_time = time.time() - start

    avg_case_target = random.choice(arr)
    start = time.time()
    binary_search(arr, avg_case_target)
    avg_case_time = time.time() - start

    print(f"Best case time: {best_case_time:.6f} seconds")
    print(f"Worst case time: {worst_case_time:.6f} seconds")
    print(f"Average case time: {avg_case_time:.6f} seconds")
