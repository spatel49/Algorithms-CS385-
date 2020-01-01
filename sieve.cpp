/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :
 * Date        :
 * Description : Sieve of Eratosthenes
 * Pledge      :
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << "Number of primes found: " << count_num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    const int max_prime_width = num_digits(max_prime_),
    primes_per_row = 80 / (max_prime_width + 1);
    int rowcounter = 1;
    if (count_num_primes() <= primes_per_row) {
        for(int i = 0; i <= limit_; i++) {
            if(is_prime_[i] == true && i != max_prime_) {
                cout << i <<" ";
            }
            if(is_prime_[i] == true && i == max_prime_) {
                cout << i;
            }
        }
    } else {
    	    for (int j = 0; j <= limit_; j++) {
                string str;
                for(int x = 0; x < max_prime_width - num_digits(j); ++x){
                    str += " ";
                }
    	    	if(is_prime_[j] == true) {
    	    		if(rowcounter != primes_per_row) {
    	    			if (j == max_prime_) {
                            cout << str << j;
    	    				rowcounter++;
    	    			} else {
    	    				cout << str << j << " ";
    	    				rowcounter++;
    	    			}
    	    			} else {
    	    				cout << str << j << endl;
    	    				rowcounter = 1;
    	    				}
    	    			}
            }
        }
    }

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found

    int counter = 0;
    for (int i=0; i<= limit_; i++){
        if (is_prime_[i]) {
            counter++;
        }
    }
    return counter;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 2; i <= limit_; i++) {
    		is_prime_[i] = true;
    	}

    for (int i=2; i <= sqrt(limit_); i++){
        if (is_prime_[i] == true){
            for (int j = i * i; j <= limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }
    num_primes_ = count_num_primes();
    for(int k = limit_; k >= 2; k--) {
        if(is_prime_[k]) {
            max_prime_ = k;
            break;
    		}
     }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int ncounter = 0;
    while (num>=1) {
        ncounter++;
        num = num / 10;
    }
    return ncounter;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve ListOfPrimes = PrimesSieve(limit);
    cout << endl;
    ListOfPrimes.display_primes();
    return 0;
}
