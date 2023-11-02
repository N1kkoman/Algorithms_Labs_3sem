#include <iostream>
#include <vector>

using namespace std;


int partition(vector<int>& arr, int left, int right){
    int pivot = arr[right]; // выбираем опорный элемент
    int i = left; // индекс для элементов меньше опорного
    // каждый раз, когда мы находим элемент, меньший или равный опорному, i
    // увеличивается, и этот элемент будет помещен перед опорной точкой.
    for (int j = left; j <= right; j++){
        if (arr[j] < pivot){ // делим элементы вектора на две части:         
            swap(arr[i], arr[j]); // слева будут находиться элементы меньше опорного, а справа - элементы больше опорного
            i++;
        }
    }
    swap(arr[i], arr[right]); // перемещаем опорный элемент на правильную позицию
    return i; // возвращаем индекс опорного элемента
}
// Функция, которая сортирует последовательность чисел методом быстрой сортировки
void quick_sort(vector<int>& arr, int left, int right) {
    if (left < right){
        int pivot = partition(arr, left, right); // получаем индекс опорного элемента

        quick_sort(arr, left, pivot - 1); // рекурсивно сортируем левую и правую часть массива
        quick_sort(arr, pivot + 1, right);
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

    // Сортируем последовательность чисел методом быстрой сортировки
    quick_sort(arr, 0, arr.size() - 1);
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

