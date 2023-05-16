// Include necessary libraries
#include <boost/multiprecision/cpp_int.hpp> // For using boost multi-precision integer
#include <boost/multiprecision/cpp_dec_float.hpp> // For using boost multi-precision decimal float
#include <boost/math/constants/constants.hpp> // For using mathematical constants
#include <fstream> // For file handling
#include <iostream> // For input/output
#include <string> // For using string

// Bring names from the boost::multiprecision namespace into the current scope
using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_100;

// Define constant file names
constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

// Function implementing the Chudnovsky algorithm to calculate pi to a given number of decimal places
cpp_dec_float_100 chudnovsky_algorithm(size_t decimal_places) {
    cpp_int k_fact = 1; // Factorial of k
    cpp_int a_k = 1; // a_k in the series sum
    cpp_int b_k = 0; // b_k in the series sum
    cpp_int C = 640320; // Constant C in the series sum
    cpp_int C3_over_24 = C * C * C / 24; // C cubed over 24
    cpp_dec_float_100 sum_a = 1; // Sum of a_k series
    cpp_dec_float_100 sum_b = 0; // Sum of b_k series
    cpp_dec_float_100 k_dec; // Decimal representation of k

    // Calculate the series sum up to the specified number of decimal places
    for (size_t k = 1; k <= decimal_places; ++k) {
        k_fact *= k; // Calculate factorial of k
        a_k *= -((6 * k - 5) * (2 * k - 1) * (6 * k - 1)); // Update a_k
        b_k += k; // Update b_k
        sum_a += cpp_dec_float_100(a_k) / cpp_dec_float_100(k_fact * k_fact * k_fact); // Update sum of a_k series
        sum_b += cpp_dec_float_100(b_k) / cpp_dec_float_100(k_fact * k_fact * k_fact); // Update sum of b_k series
        k_dec = k; // Convert k to decimal
    }

    // Calculate pi using the Chudnovsky formula
    cpp_dec_float_100 sqrt_10005 = sqrt(cpp_dec_float_100(10005)); // Square root of 10005
    cpp_dec_float_100 pi = (13591409 * sum_a + 545140134 * sum_b) * sqrt_10005; // Pi approximation
    pi /= 426880 * sum_b; // Adjust pi approximation

    return 1 / pi; // Return the inverse of pi as the Chudnovsky algorithm computes 1/pi
}

int main() {
    // Open input file
    std::ifstream input(input_file);
    if (!input.is_open()) { // If file cannot be opened, output error and exit with return code 1
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    size_t decimal_places; // Declare a variable to store the number of decimal places from the input file
    input >> decimal_places; // Read the number from the file
    input.close(); // Close the input file

    // Calculate pi to the specified number of decimal places
    cpp_dec    _float_100 pi = chudnovsky_algorithm(decimal_places);

    // Open output file
    std::ofstream output(output_file);
    if (!output.is_open()) { // If file cannot be opened, output error and exit with return code 1
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    // Set the precision of the output to the number of decimal places
    output.precision(decimal_places);
    // Output the calculated value of pi to the file
    output << std::fixed << pi << std::endl;
    output.close(); // Close the output file

    return 0; // Exit with return code 0
}

