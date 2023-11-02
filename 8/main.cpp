#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция, которая сортирует последовательность чисел методом поразрядной сортировки
void radix_sort(vector<int>& arr) {
    // Находим максимальное число в последовательности
    int max_num = *max_element(arr.begin(), arr.end());
    
    // Выполняем поразрядную сортировку для каждого разряда числа
    for (int exp = 1; max_num / exp > 0; exp *= 10) {
        // Создаем векторы корзин для каждого разряда (от 0 до 9)
        vector<int> buckets[10];
        
        // Распределяем числа по корзинам в соответствии с текущим разрядом
        for (int num : arr) {
            int digit = (num / exp) % 10;
            buckets[digit].push_back(num);
        }
        
        // Объединяем числа из корзин в исходный вектор
        int index = 0;
        for (int i = 0; i < 10; i++) {
            for (int num : buckets[i]) {
                arr[index++] = num;
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
    radix_sort(arr);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}


