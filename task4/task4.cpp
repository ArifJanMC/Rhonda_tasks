#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

double chudnovsky_algorithm(size_t decimal_places) {
    double k_fact = 1;
    double a_k = 1;
    double b_k = 0;
    double C = 640320;
    double C3_over_24 = C * C * C / 24;
    double sum_a = 1;
    double sum_b = 0;
    double k_dec;

    for (size_t k = 1; k <= decimal_places; ++k) {
        k_fact *= k;
        a_k *= -((6 * k - 5) * (2 * k - 1) * (6 * k - 1));
        b_k += k;
        sum_a += a_k / (k_fact * k_fact * k_fact);
        sum_b += b_k / (k_fact * k_fact * k_fact);
        k_dec = k;
    }

    double sqrt_10005 = sqrt(10005.0);
    double pi = (13591409 * sum_a + 545140134 * sum_b) * sqrt_10005;
    pi /= 426880 * sum_b;

    return 1 / pi;
}

int main() {
    std::ifstream input(input_file);
    if (!input.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    size_t decimal_places;
    input >> decimal_places;
    input.close();

    double pi = chudnovsky_algorithm(decimal_places);

    std::ofstream output(output_file);
    if (!output.is_open()) {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    output.precision(decimal_places);
    output << std::fixed << pi << std::endl;
    output.close();

    return 0;
}
