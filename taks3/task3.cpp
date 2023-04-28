#include <cstdio>
#include <cstdlib>

constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

int main() {
    FILE* input = fopen(input_file, "rb");
    if (input == nullptr) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE* output = fopen(output_file, "wb");
    if (output == nullptr) {
        fclose(input);
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    constexpr size_t buffer_size = 4096;
    char buffer[buffer_size];

    while (true) {
        size_t bytes_read = fread(buffer, 1, buffer_size, input);
        if (bytes_read == 0) {
            break;
        }
        size_t bytes_written = fwrite(buffer, 1, bytes_read, output);
        if (bytes_written != bytes_read) {
            perror("Error writing to output file");
            fclose(input);
            fclose(output);
            exit(EXIT_FAILURE);
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
