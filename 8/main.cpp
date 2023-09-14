#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом кучи
void heap_sort(vector<int>& arr) {
    int n = arr.size();

    // Построение кучи (heapify)
    for (int i = n / 2 - 1; i >= 0; i--) {
        int j = i;
        while (2 * j + 1 < n) {
            int k = 2 * j + 1;
            if (k + 1 < n && arr[k + 1] > arr[k]) {
                k++;
            }
            if (arr[k] > arr[j]) {
                swap(arr[j], arr[k]);
                j = k;
            }
            else {
                break;
            }
        }
    }

    // Извлечение элементов из кучи в отсортированном порядке
    for (int i = n - 1; i >= 1; i--) {
        swap(arr[0], arr[i]);
        int j = 0;
        while (2 * j + 1 < i) {
            int k = 2 * j + 1;
            if (k + 1 < i && arr[k + 1] > arr[k]) {
                k++;
            }
            if (arr[k] > arr[j]) {
                swap(arr[j], arr[k]);
                j = k;
            }
            else {
                break;
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

    // Сортируем последовательность чисел методом кучи
    heap_sort(arr);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}


