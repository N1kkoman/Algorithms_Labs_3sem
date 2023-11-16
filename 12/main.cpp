#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <istream>
#include <limits>
#include <queue>
#include <string>
#include <vector>

struct MinHeapNode {
    int element;
    int index;
};

struct Comp {
    bool operator()(const MinHeapNode& left, const MinHeapNode& right) const {
        return left.element > right.element;
    }
};

std::fstream open_file(const std::string& file_name,
    std::ios_base::openmode mode) {
    std::fstream fp{};
    fp.open(file_name, mode);
    if (!fp.is_open()) {
        std::cerr << "Error while opening the file.\n";
        throw std::runtime_error("Can't open!");
    }
    return fp;
}

void merge_sort_a(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}

void merge_files(const std::string& output_file, int n, int k) {

    std::vector<std::string> input_files{};
    for (int i = 0; i < k; i++) {
        input_files.emplace_back(std::to_string(i));
    }

    auto out = open_file(output_file, std::ios::out);

    std::vector<MinHeapNode> harr(k);
    std::priority_queue<MinHeapNode, std::vector<MinHeapNode>, Comp> pq;

    int i;
    for (i = 0; i < k; i++) {
        auto in = open_file(input_files.at(i), std::ios::in);
        if (in >> harr[i].element) {
            harr[i].index = i;
            pq.push(harr[i]);
            in.close();
            continue;
        }
        in.close();
        break;
    }

    int count = 0;

    FILE* in[100];
    for (int i = 0; i < k; i++)
        in[i] = fopen(std::to_string(i).c_str(), "r");

    auto temp{ 0 };

    while (count != i) {
        MinHeapNode root = pq.top();
        pq.pop();

        if (temp == root.element)
            std::cout << "same element" << std::endl;
        else
            out << root.element << " ";

        temp = root.element;
        auto t = fscanf(in[root.index], "%d ", &root.element);
        if (t != 1) {
            root.element = std::numeric_limits<int>::max();
            count++;
        }
        pq.push(root);
    }
    for (int i = 0; i < k; i++)
        fclose(in[i]);

    out.close();
}

void create_initial_files(const std::string& input_file, int run_size,
    int num_ways) {

    auto in = open_file(input_file, std::ios::in);

    std::fstream out;
    std::string file_name{};
    std::vector<std::string> out_files{};

    for (int i = 0; i < num_ways; i++) {
        file_name = std::to_string(i) + ".txt";
        out = open_file(file_name, std::ios::out);
        out_files.emplace_back(std::to_string(i));
        out.close();
    }

    std::vector<int> vec{};

    bool more_input{ true };
    int next_output_file{ 0 };

    int i{};
    int temp{};
    while (more_input) {
        for (i = 0; i < run_size; i++) {
            if (in >> temp) {
                vec.emplace_back(temp);
            }
            else {
                more_input = false;
                break;
            }
        }

        merge_sort_a(vec);

        for (int j = 0; j < i; j++) {
            out = open_file(out_files[next_output_file], std::ios::app);
            out << vec[j] << " ";
            out.close();
        }
        next_output_file++;
        vec.clear();
    }
    in.close();
}

void start_tw() {
    constexpr int count_of_files{ 5 };
    constexpr int elements_in_file{ 20 };

    std::string input_file{ "input.txt" };
    std::string output_file{ "output.txt" };
    auto in = open_file(input_file, std::ios::out);
    int arr[] = { -88, -80, -3,  -73, 18,  -20, -61, 94,  89,  42,  -62, -84, -50,
                 -59, 86,  -27, -95, 20,  -33, 62,  48,  -68, 3,   70,  36,  23,
                 85,  -96, -41, 24,  74,  -21, -99, 97,  0,   91,  -11, 84,  -72,
                 6,   -66, -31, -8,  8,   -26, -89, 75,  -64, 59,  -94, 40,  29,
                 43,  -38, 14,  47,  -76, 73,  -29, 98,  -49, -9,  100, -52, 92,
                 -19, -34, 87,  -42, -22, 67,  -91, -10, 41,  -54, -51, 79,  -63,
                 -28, -36, -30, 15,  64,  10,  35,  -32, -97, 37,  60,  -87, 1,
                 -24, -56, -46, 39,  46,  77,  -90, -16, -67 };

    for (int i = 0; i < sizeof arr / sizeof arr[0]; i++) {
        in << arr[i] << " ";
    }

    in.close();

    create_initial_files(input_file, elements_in_file,
        count_of_files);
    merge_files(output_file, elements_in_file,
        count_of_files);
}

int main() {
    void start_tw();
}