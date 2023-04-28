#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include <fstream>
#include <iostream>
#include <string>

using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_100;

constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

cpp_dec_float_100 chudnovsky_algorithm(size_t decimal_places) {
    cpp_int k_fact = 1;
    cpp_int a_k = 1;
    cpp_int b_k = 0;
    cpp_int C = 640320;
    cpp_int C3_over_24 = C * C * C / 24;
    cpp_dec_float_100 sum_a = 1;
    cpp_dec_float_100 sum_b = 0;
    cpp_dec_float_100 k_dec;

    for (size_t k = 1; k <= decimal_places; ++k) {
        k_fact *= k;
        a_k *= -((6 * k - 5) * (2 * k - 1) * (6 * k - 1));
        b_k += k;
        sum_a += cpp_dec_float_100(a_k) / cpp_dec_float_100(k_fact * k_fact * k_fact);
        sum_b += cpp_dec_float_100(b_k) / cpp_dec_float_100(k_fact * k_fact * k_fact);
        k_dec = k;
    }

    cpp_dec_float_100 sqrt_10005 = sqrt(cpp_dec_float_100(10005));
    cpp_dec_float_100 pi = (13591409 * sum_a + 545140134 * sum_b) * sqrt_10005;
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

    cpp_dec_float_100 pi = chudnovsky_algorithm(decimal_places);

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
