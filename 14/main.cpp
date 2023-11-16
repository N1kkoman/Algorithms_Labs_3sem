#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Функция для добавления значения в таблицу
void putInTable(std::vector<std::vector<std::string>>& table, int myhash, std::string value) {
    table[myhash].push_back(value);
}

int main() {
    std::ifstream file("input.txt");
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    // Разделение текста на отдельные слова
    while (ss >> word) {
        words.push_back(word);
    }

    // Создание таблицы с двойным размером от количества слов
    std::vector<std::vector<std::string>> table(words.size() * 2);
    for (const std::string& word : words) {
        int temp_sum = 0;
        for (char c : word) {
            // Если символ является знаком препинания, добавляем его в таблицу
            if (c == '!' || c == '.' || c == ',' || c == '?' || c == ';' || c == '\'') {
                int myhash = c % table.size();
                putInTable(table, myhash, std::string(1, c));
                // Удаляем знак препинания из слова
                std::string word = word.substr(0, word.length() - 1);
            }
            temp_sum += static_cast<int>(c);
        }
        // Вычисление хэша для слова и добавление его в таблицу
        int myhash = temp_sum % table.size();
        putInTable(table, myhash, word);
    }

    std::ofstream output("table.txt");
    for (int i = 0; i < table.size(); ++i) {
        std::string temp_string = std::to_string(i) + " : ";
        // Формирование строки с элементами таблицы
        for (const std::string& value : table[i]) {
            temp_string += value + " ";
        }
        temp_string += "\n";
        // Запись строки в файл
        output << temp_string;
    }
    output.close();

    return 0;
}
