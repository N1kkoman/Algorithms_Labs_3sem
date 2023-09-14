#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом вставки
void insertion_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { // проходим по всем элементам, которые находятся левее текущего элемента и больше его
            arr[j + 1] = arr[j]; // сдвигаем элементы, которые больше текущего элемента, на одну позицию вправо
            j--;
        }
        arr[j + 1] = key; // вставляем текущий элемент на свое место

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

    // Сортируем последовательность чисел методом вставки
    insertion_sort(arr);

    // Выводим отсортированную последовательность чисел в консоль
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
