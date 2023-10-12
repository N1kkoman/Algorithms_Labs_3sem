#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для нахождения максимального по модулю числа в массиве
int findMaxAbs(vector<int>& arr) {
    int maxNum = abs(arr[0]);
    for (int num : arr) {
        if (abs(num) > maxNum) {
            maxNum = abs(num);
        }
    }
    return maxNum;
}

// Функция, которая сортирует последовательность чисел методом поразрядной сортировки
void radix_sort(vector<int>& arr) {
    int maxNum = findMaxAbs(arr);

    // Выполняем цикл для каждого разряда, начиная с младшего и заканчивая старшим
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        // Создаем временный вектор для отсортированных элементов на текущем разряде
        vector<int> output(arr.size());
        // Создаем вспомогательный вектор для подсчета количества элементов на каждом разряде
        vector<int> count(19);

        // Проходим по исходному вектору и увеличиваем соответствующий счетчик в векторе count для текущего разряда
        for (int i = 0; i < arr.size(); i++) {
            int index = (arr[i] / exp) % 10 + 9;
            count[index]++;
        }

        // Выполняем префиксную сумму на векторе count, чтобы определить позиции, на которые будут помещены элементы в вектор output
        for (int i = 1; i < 19; i++) {
            count[i] += count[i - 1];
        }

        // Проходим по исходному вектору в обратном порядке и для каждого элемента определяем его позицию на текущем разряде
        // Затем помещаем элемент на соответствующую позицию во временном векторе output и уменьшаем соответствующий счетчик в векторе count
        for (int i = arr.size() - 1; i >= 0; i--) {
            int index = (arr[i] / exp) % 10 + 9;
            output[count[index] - 1] = arr[i];
            count[index]--;
        }

        // Копируем отсортированные элементы из временного вектора output обратно в исходный вектор arr
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = output[i];
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


