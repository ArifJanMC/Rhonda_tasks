// Include necessary libraries
#include <fstream> // for file handling
#include <iostream> // for input/output
#include <vector> // for using vector

// Define constant file names
constexpr const char* input_file = "input.txt";
constexpr const char* output_file = "output.txt";

// Function implementing Sieve of Eratosthenes algorithm to find all primes up to n
std::vector<bool> sieve_of_eratosthenes(int n) {
    std::vector<bool> is_prime(n + 1, true); // Create a boolean vector of size n+1 and initialize all elements as true
    is_prime[0] = false; // Set 0 as non-prime
    is_prime[1] = false; // Set 1 as non-prime

    // Implement Sieve of Eratosthenes algorithm
    for (int i = 2; i * i <= n; ++i) {
        if (is_prime[i]) { // If i is a prime number
            for (int j = i * i; j <= n; j += i) { // Mark multiples of i as non-prime
                is_prime[j] = false;
            }
        }
    }

    return is_prime; // Return the vector indicating prime numbers
}

int main() {
    // Open input file
    std::ifstream input(input_file);
    if (!input.is_open()) { // If file cannot be opened, output error and exit with return code 1
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    int n; // Declare a variable to store the number from the input file
    input >> n; // Read the number from the file
    input.close(); // Close the input file

    // Get the vector indicating prime numbers up to n
    std::vector<bool> is_prime = sieve_of_eratosthenes(n);

    // Open output file
    std::ofstream output(output_file);
    if (!output.is_open()) { // If file cannot be opened, output error and exit with return code 1
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    bool first = true; // Flag to track if this is the first prime number
    for (int i = 2; i <= n; ++i) { // Iterate through numbers from 2 to n
        if (is_prime[i]) { // If i is a prime number
            if (first) { // If this is the first prime number, unset the flag
                first = false;
            } else { // If this is not the first prime number, append a comma before it
                output << ", ";
            }
            output << i; // Output the prime number to the file
        }
    }
    output << std::endl; // Append a newline at the end
    output.close(); // Close the output file

    return 0; // Exit with return code 0
}
