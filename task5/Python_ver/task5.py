def sieve_of_eratosthenes(n):
    primes = [True for i in range(n+1)]
    p = 2
    while p * p <= n:
        if primes[p] is True:
            for i in range(p * p, n+1, p):
                primes[i] = False
        p += 1
    prime_numbers = [p for p in range(2, n) if primes[p]]
    return prime_numbers

def write_primes_to_file(primes, filename):
    with open(filename, 'w') as f:
        f.write(', '.join(map(str, primes)))

def read_number_from_file(filename):
    with open(filename, 'r') as f:
        number = int(f.read())
    return number

def main():
    input_filename = 'input.txt'
    output_filename = 'output.txt'

    n = read_number_from_file(input_filename)
    primes = sieve_of_eratosthenes(n)
    write_primes_to_file(primes, output_filename)

if __name__ == "__main__":
    main()
