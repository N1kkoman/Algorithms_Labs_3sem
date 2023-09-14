#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом выбора
void selection_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
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

    // Сортируем последовательность чисел методом выбора
    selection_sort(arr);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
