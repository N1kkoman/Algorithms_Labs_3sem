#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <string>

int main() {
    std::unordered_map<std::string, std::list<std::string>> hashTable; // Создаем пустую хеш-таблицу с использованием списков
    std::ifstream inputFile("input.txt"); // Открываем файл для чтения
    std::ofstream outputFile("output.txt"); // Открываем файл для записи

    if (inputFile.is_open() && outputFile.is_open()) { // Проверяем, что файлы открыты успешно
        std::string line;
        while (std::getline(inputFile, line)) { // Читаем файл построчно
            size_t hashValue = std::hash<std::string>{}(line); // Вычисляем хеш-значение для строки
            hashTable[std::to_string(hashValue)].push_back(line); // Добавляем элемент в хеш-таблицу с использованием списка
        }

        for (auto const& [key, value] : hashTable) { // Записываем хеш-таблицу в файл
            outputFile << key << " : ";
            for (const auto& item : value) {
                outputFile << item << " ";
            }
            outputFile << "\n";
        }

        inputFile.close(); // Закрываем файлы
        outputFile.close();
    }
    else {
        std::cout << "Unable to open input or output file\n"; // Выводим сообщение об ошибке, если файлы не открыты
    }

    return 0;
}
