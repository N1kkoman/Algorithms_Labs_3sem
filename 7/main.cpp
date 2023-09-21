#include <iostream>
#include <vector>

using namespace std;

// Функция, которая сортирует последовательность чисел методом Шелла
void shell_sort(vector<int>& arr) {
    int n = arr.size(); 
    for (int gap = n / 2; gap > 0; gap /= 2) { // внешний цикл, задающий размер шага
        for (int i = gap; i < n; i++) { // внутренний цикл, выполняющий сортировку подпоследовательностей
            int temp = arr[i]; 
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) { // цикл сдвига элементов вправо, если текущий элемент меньше предыдущего
                arr[j] = arr[j - gap]; // сдвигаем элементы вправо
            }
            arr[j] = temp; // помещаем текущий элемент на освободившееся место
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



