#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);  
    vector<int> count(10, 0);  

    
    for (int i = 0; i < n; i++) {
        int index = arr[i] / exp;
        count[index % 10]++;
    }

    
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    
    for (int i = n - 1; i >= 0; i--) {
        int index = arr[i] / exp;
        output[count[index % 10] - 1] = arr[i];
        count[index % 10]--;
    }

    
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}


vector<int> radixSort(vector<int> arr) {
    
    int maxVal = *max_element(arr.begin(), arr.end());

    
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
    return arr;
}

int main() {
    vector<int> arr = {20,10,30,60,50,40,70,90,80};
    
    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    arr = radixSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}