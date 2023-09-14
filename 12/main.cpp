#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом слияния
void merge_sort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = (left + right) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (int i = left; i <= right; i++) {
        arr[i] = temp[i - left];
    }
}

int main() {
    // Считываем последовательность чисел из консоли
    vector<int> arr;
    int x;
    while (cin >> x) {
        arr.push_back(x);
        if (cin.get() == '\n') {
            break;
        }
    }

    // Сортируем последовательность чисел методом слияния
    merge_sort(arr, 0, arr.size() - 1);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

while (cin >> x) {
    arr.push_back(x);
    if (cin.get() == '\n') {
        break;
    }
}


