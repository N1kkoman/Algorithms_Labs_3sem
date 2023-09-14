#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом быстрой сортировки
void quick_sort(vector<int>& arr, int left, int right) {
    if (left >= right) { // базовый случай: если левая граница больше или равна правой, то массив уже отсортирован
        return;
    }
    int pivot = arr[(left + right) / 2]; // выбираем опорный элемент как средний элемент в диапазоне
    int i = left, j = right; // индексы для прохода по массиву в разных направлениях
    while (i <= j) { // цикл разделения диапазона на две части
        while (arr[i] < pivot) { // ищем элементы, которые нужно переставить в левую часть
            i++;
        }
        while (arr[j] > pivot) { // ищем элементы, которые нужно переставить в правую часть
            j--;
        }
        if (i <= j) { // меняем элементы местами
            swap(arr[i], arr[j]);
            i++; 
            j--; 
        }
    }
    quick_sort(arr, left, j);
    quick_sort(arr, i, right); 
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

    // Сортируем последовательность чисел методом быстрой сортировки
    quick_sort(arr, 0, arr.size() - 1);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

