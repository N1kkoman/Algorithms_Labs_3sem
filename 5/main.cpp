#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом вставки
void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++)                            // проходим по всем элементам, которые находятся левее текущего элемента и больше его
        for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) // сдвигаем элементы, которые больше текущего элемента, на одну позицию вправо
            swap(arr[j - 1], arr[j]);
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

    // Сортируем последовательность чисел методом вставки
    insertion_sort(arr);

    // Выводим отсортированную последовательность чисел в консоль
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
