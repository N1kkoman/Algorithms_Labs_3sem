#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом Шелла
void shell_sort(vector<int>& arr) {
    int n = arr.size(); 
    for (int gap = n / 2; gap > 0; gap /= 2) { // Внешний цикл, задающий размер шага
        for (int i = gap; i < n; i++) { // Выполняем сортировку вставками с заданным шагом
            int temp = arr[i]; // Сохраняем a[i] в temp и создаем пустое место на позиции i
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { // Сдвигаем ранее отсортированные элементы по шагу вправо до тех пор, пока не найдем правильное место для arr[i]
                arr[j] = arr[j - gap];
            }
            arr[j] = temp; //  помещаем temp (исходный a[i]) в его правильное место
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

    // Сортируем последовательность чисел методом Шелла
    shell_sort(arr);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}



