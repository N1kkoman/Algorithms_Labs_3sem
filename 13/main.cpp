#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, std::string> hashTable; // Создаем пустую хеш-таблицу
    std::ifstream inputFile("input.txt"); // Открываем файл для чтения
    std::ofstream outputFile("output.txt"); // Открываем файл для записи

    if (inputFile.is_open() && outputFile.is_open()) { // Проверяем, что файлы открыты успешно
        std::string line;
        while (std::getline(inputFile, line)) { // Читаем файл построчно
            size_t hashValue = std::hash<std::string>{}(line); // Вычисляем хеш-значение для строки
            auto search = hashTable.find(std::to_string(hashValue)); // Ищем элемент в хеш-таблице по ключу - хеш-значению строки
            if (search != hashTable.end()) { // Если элемент найден, значит возникла коллизия
                search->second += "\n" + line; // Добавляем новую строку к уже существующей строке с таким же хеш-значением
            } else {
                hashTable.emplace(std::to_string(hashValue), line); // Добавляем элемент в хеш-таблицу
            }
        }

        for (auto const& [key, value] : hashTable) { // Записываем хеш-таблицу в файл
            outputFile << key << " : " << value << "\n";
        }

        inputFile.close(); // Закрываем файлы
        outputFile.close();
    } else {
        std::cout << "Unable to open input or output file\n"; // Выводим сообщение об ошибке, если файлы не открыты
    }

    return 0;
}
