#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом выбора
void selection_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) { // Проходимся по всем элементам массива, начиная с первого и заканчивая предпоследним
        int min_idx = i; // Предполагаем, что минимальный элемент находится на текущей позиции
        for (int j = i + 1; j < n; j++) { // Находим минимальный элемент в оставшейся части массива, начиная с текущей позиции
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]); // Меняем местами текущий элемент с минимальным найденным элементом
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
