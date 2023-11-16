#include <iostream>
#include <fstream> 
#include <vector>
#include <string>

// Функция для добавления элемента в хеш-таблицу
bool putInTable(int myhash, const std::string& value, std::vector<std::string>& table) {
    // Проходим по списку элементов с заданным хеш-значением
    for (int i = myhash; i < table.size(); ++i) {
        // Если в списке есть свободное место, добавляем элемент
        if (table[i].empty()) {
            table[i] = value;
            return true;
        }
    }
    // Если в списке нет свободного места, возвращаем false
    return false;
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть входной файл 'example.txt'" << std::endl;
        return 1;
    }

    std::vector<std::string> words; // Создаем вектор для хранения слов
    std::string word;
    while (inputFile >> word) {
        // Удаляем пунктуацию из слова
        std::string cleanedWord;
        for (char c : word) {
            if (c != '!' && c != '.' && c != ',' && c != '?' && c != ';' && c != '\'') {
                cleanedWord += c;
            }
        }
        words.push_back(cleanedWord); // Добавляем очищенное слово в вектор слов
    }
    inputFile.close(); // Закрываем файл после чтения

    std::vector<std::string> table(words.size() * 2); // Создаем хеш-таблицу

    for (const std::string& word : words) {
        int tempSum = 0;
        for (char c : word) {
            tempSum += static_cast<int>(c); // Считаем сумму ASCII-кодов символов в слове
        }

        int myhash = tempSum % table.size(); // Вычисляем хеш-значение для слова

        // Добавляем слово в хеш-таблицу с помощью функции putInTable()
        if (!putInTable(myhash, word, table)) {
            putInTable(myhash, word, table);
        }
    }


    std::ofstream outputFile("table.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Не удалось открыть выходной файл 'table.txt'" << std::endl;
        return 1;
    }

    // Выводим таблицу в файл
    for (int i = 0; i < table.size(); ++i) {
        outputFile << i << " : " << table[i] << "\n";
    }

    outputFile.close(); 

    std::cout << "Таблица записана в файл 'table.txt'" << std::endl;

    return 0; 
}
