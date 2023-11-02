#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


class PolyphaseMergeSort {
private:
    std::vector<int> noSortList; // Исходный список для сортировки
    std::vector<std::vector<int>> arrayParts; // Подсписки, на которые разделен исходный список
    bool sortFlag; // Флаг, указывающий на то, была ли уже выполнена сортировка

    void arrayToParts() {
        // Разделение исходного списка на подсписки
        arrayParts.clear();
        for (int i = 0; i < noSortList.size(); i += 2500) {
            std::vector<int> part(noSortList.begin() + i, noSortList.begin() + std::min(i + 2500, static_cast<int>(noSortList.size())));
            arrayParts.push_back(part);
        }
    }

    std::vector<int> merge(std::vector<int> left, std::vector<int> right) {
        // Слияние двух отсортированных списков в один
        std::vector<int> result;
        int leftIndex = 0;
        int rightIndex = 0;
        
        while (leftIndex < left.size() && rightIndex < right.size()) {
            if (left[leftIndex] < right[rightIndex]) {
                result.push_back(left[leftIndex]);
                leftIndex++;
            } else {
                result.push_back(right[rightIndex]);
                rightIndex++;
            }
        }
        
        while (leftIndex < left.size()) {
            result.push_back(left[leftIndex]);
            leftIndex++;
        }
        
        while (rightIndex < right.size()) {
            result.push_back(right[rightIndex]);
            rightIndex++;
        }
        
        return result;
    }

    std::vector<int> mergeSort(std::vector<int> list) {
        // Сортировка списка методом слияния
        if (list.size() < 2) {
            return list;
        } else {
            int middle = list.size() / 2;
            std::vector<int> left(list.begin(), list.begin() + middle);
            std::vector<int> right(list.begin() + middle, list.end());
            left = mergeSort(left);
            right = mergeSort(right);
            return merge(left, right);
        }
    }

public:
    PolyphaseMergeSort(std::vector<int> list) : noSortList(list), sortFlag(false) {
        arrayToParts();
    }

    std::vector<int> sorted() {
        // Возвращает отсортированный список, если уже отсортирован, иначе сортирует и возвращает
        if (sortFlag) {
            return noSortList;
        } else {
            sort();
            return noSortList;
        }
    }

    void sort() {
        // Сортировка подсписков и объединение их в один список
        for (int subArrayIndex = 0; subArrayIndex < arrayParts.size(); subArrayIndex++) {
            arrayParts[subArrayIndex] = mergeSort(arrayParts[subArrayIndex]); // Сортировка каждого подсписка методом слияния
        }
        
        std::vector<int> tempBigList;
        for (int subArrayIndex = 0; subArrayIndex < arrayParts.size(); subArrayIndex++) {
            tempBigList.insert(tempBigList.end(), arrayParts[subArrayIndex].begin(), arrayParts[subArrayIndex].end()); // Объединение отсортированных подсписков
        }
        
        noSortList = mergeSort(tempBigList); // Сортировка объединенного списка методом слияния
        sortFlag = true; // Установка флага сортировки
    }
};


void saveToFile(const std::string& filename, const std::vector<int>& sortedList) {
    // Сохранение отсортированного списка в файл
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& num : sortedList) {
            file << num << std::endl;
        }
        file.close();
        std::cout << "Sorted sequence has been saved to " << filename << std::endl;
    } else {
        std::cout << "Unable to open file " << filename << std::endl;
    }
}


int main() {
    // Чтение входного файла
    std::ifstream inputFile("input.txt");
    
    if (!inputFile.is_open()) {
        std::cout << "Unable to open input file" << std::endl;
        return 1;
    }
    
    std::vector<int> inputList;
    int num;
    
    while (inputFile >> num) {
        inputList.push_back(num);
    }
    
    inputFile.close();
    
    // Сортировка списка и сохранение в выходной файл
    PolyphaseMergeSort mergeSort(inputList);
    std::vector<int> sortedList = mergeSort.sorted();
    
    saveToFile("output.txt", sortedList);
    
    return 0;
}
