#include <fstream>
#include <iostream>
#include <vector>

constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

std::vector<bool> sieve_of_eratosthenes(int n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    return is_prime;
}

int main() {
    std::ifstream input(input_file);
    if (!input.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    int n;
    input >> n;
    input.close();

    std::vector<bool> is_prime = sieve_of_eratosthenes(n);

    std::ofstream output(output_file);
    if (!output.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    bool first = true;
    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) {
            if (first) {
                first = false;
            } else {
                output << ", ";
            }
            output << i;
        }
    }
    output << std::endl;
    output.close();

    return 0;
}
