#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом пузырька
void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
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

    // Сортируем последовательность чисел методом пузырька
    bubble_sort(arr);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
