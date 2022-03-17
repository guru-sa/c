#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>
#include <mutex>

using namespace std;

const int MaxCount = 150000;
const int ThreadCount = 4;

bool IsPrimeNumber(int number) {
    if (number == 1) 
        return false;
    if (number == 2 || number == 3) 
        return false;
    for ( int i = 2; i < number - 1; i++) {
        if ((number % i) == 0)
            return false;
    }
    return true;
}

void PrintNumbers(const vector<int>& primes) {
    for (int v : primes) {
        cout << v << endl;
    }
}

int main() {
    int num = 1;
    recursive_mutex num_mutex;
    vector<int> primes;
    recursive_mutex primes_mutex;

    chrono::system_clock::time_point start_time = chrono::system_clock::now();

    vector<shared_ptr<thread> > threads;

    for (int i = 0; i < ThreadCount; i++) {
        shared_ptr<thread> t(new thread([&]() {
            while (true) {
                int n;
                {
                    lock_guard<recursive_mutex> num_lock(num_mutex);
                    n = num;
                    num++;
                }
                if (n >= MaxCount)
                    break;

                if (IsPrimeNumber(n)) {
                    lock_guard<recursive_mutex> primes_mutex(primes_mutex);
                    primes.push_back(n);
                }
            }
        }));
        threads.push_back(t);
    }

    for (shared_ptr<thread> t : threads) {
        t->join();
    }

    chrono::system_clock::time_point end_time = chrono::system_clock::now();

    long long duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Took" << duration << " milliseconds." << endl;

    // PrintNumbers(primes);

    return 0;
}

