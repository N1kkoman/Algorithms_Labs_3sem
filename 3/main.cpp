#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция, которая находит все числа от 1 до x, удовлетворяющие условию 3^K * 5^L * 7^M = x
vector<int> findNumbers(int x) {
    vector<int> result;

    // Проходим по всем возможным значениям K, L и M
    for (int k = 0; pow(3, k) <= x; k++) {
        for (int l = 0; pow(3, k) * pow(5, l) <= x; l++) {
            for (int m = 0; pow(3, k) * pow(5, l) * pow(7, m) <= x; m++) {
                int num = pow(3, k) * pow(5, l) * pow(7, m);
                if (num <= x) {
                    result.push_back(num);
                }
            }
        }
    }

    // Сортируем полученный вектор чисел по возрастанию
    sort(result.begin(), result.end());

    return result;
}

// Функция, которая выводит все числа от 1 до x, удовлетворяющие условию 3^K * 5^L * 7^M = x
void printNumbers(int x) {
    vector<int> numbers = findNumbers(x);
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int x;
    cout << "Введите число x: ";
    cin >> x;

    cout << "Числа от 1 до x, удовлетворяющие условию 3^K * 5^L * 7^M = x: ";
    printNumbers(x);

    return 0;
}
