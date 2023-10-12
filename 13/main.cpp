#include <iostream>
#include <fstream>
#include <unordered_map>
#include <list>
#include <sstream>
#include <string>
#include <cctype>

int main() {
    std::unordered_map<std::string, std::list<std::string>> hashTable; // Создаем пустую хеш-таблицу с использованием списков
    std::ifstream inputFile("input.txt"); // Открываем файл для чтения
    std::ofstream outputFile("output.txt"); // Открываем файл для записи

    if (inputFile.is_open() && outputFile.is_open()) { // Проверяем, что файлы открыты успешно
        std::string line;
        while (std::getline(inputFile, line)) { // Читаем файл построчно
            std::string word;
            std::istringstream iss(line);
            while (iss >> word) { // Разбиваем строку на слова
                // Очищаем слово от знаков препинания
                word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c) { return std::ispunct(c); }), word.end());

                if (!word.empty()) { // Если слово не пустое, то добавляем его в хеш-таблицу
                    unsigned int hashValue = std::hash<std::string>{}(word); // Вычисляем хеш-значение для слова
                    hashTable[std::to_string(hashValue)].push_back(word); // Добавляем элемент в хеш-таблицу с использованием списка
                }
            }
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
