#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>

// Comparator for min heap
struct Compare {
    bool operator()(const uint32_t& a, const uint32_t& b) {
        return a > b;
    }
};

void external_sort(const std::string& input_file, const std::string& output_file, size_t buffer_size) {
    // Read input file in chunks, sort each chunk and save them into temporary files
    std::ifstream input(input_file, std::ios::in);
    std::vector<std::string> temp_files;
    std::vector<uint32_t> buffer(buffer_size);
    size_t idx = 0;

    while (input) {
        for (idx = 0; idx < buffer_size && input >> buffer[idx]; ++idx);
        std::sort(buffer.begin(), buffer.begin() + idx);

        std::string temp_file = "temp_" + std::to_string(temp_files.size()) + ".txt";
        temp_files.push_back(temp_file);
        std::ofstream temp_output(temp_file, std::ios::out);

        for (size_t i = 0; i < idx; ++i) {
            temp_output << buffer[i] << '\n';
        }
    }

    input.close();

    // Merge sorted temporary files using a min heap
    std::ofstream output(output_file, std::ios::out);
    std::priority_queue<uint32_t, std::vector<uint32_t>, Compare> min_heap;
    std::vector<std::ifstream> temp_inputs(temp_files.size());

    for (size_t i = 0; i < temp_files.size(); ++i) {
        temp_inputs[i].open(temp_files[i], std::ios::in);
        uint32_t number;
        if (temp_inputs[i] >> number) {
            min_heap.push(number);
        }
    }

    while (!min_heap.empty()) {
        uint32_t min_number = min_heap.top();
        min_heap.pop();
        output << min_number << '\n';

        for (size_t i = 0; i < temp_files.size(); ++i) {
            if (!temp_inputs[i].eof() && min_number == std::stoi(temp_files[i])) {
                uint32_t number;
                if (temp_inputs[i] >> number) {
                    min_heap.push(number);
                }
                break;
            }
        }
    }

    for (size_t i = 0; i < temp_files.size(); ++i) {
        temp_inputs[i].close();
        remove(temp_files[i].c_str());
    }
}

int main() {
    std::string input_file = "input.txt";
    std::string output_file = "output.txt";
    size_t buffer_size = 1024; // Adjust this value based on the available RAM

    external_sort(input_file, output_file, buffer_size);

    return 0;
}
