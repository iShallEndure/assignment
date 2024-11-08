def countingSort(array, exp):
    n = len(array)
    output = [0] * n  
    count = [0] * 10  
    for i in range(n):
        index = array[i] // exp
        count[index % 10] += 1
    for i in range(1, 10):
        count[i] += count[i - 1]
    i = n - 1
    while i >= 0:
        index = array[i] // exp
        output[count[index % 10] - 1] = array[i]
        count[index % 10] -= 1
        i -= 1
    for i in range(n):
        array[i] = output[i]

def radix_sort(arr: list[int]) -> list[int]:    
    maxVal = max(array)
    exp = 1  
    while maxVal // exp > 0:
        countingSort(array, exp)
        exp *= 10  
    return array

array = [20,10,30,60,50,40,70,90,80]
print("Original array:", array)

sorted = radix_sort(array)

print("Sorted array:", sorted)
