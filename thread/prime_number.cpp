#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <memory>

using namespace std;
const int MaxCount = 150000;
const int ThreadCount = 4;

bool IsPrimeNumber(int number) 
{
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

void PrintNumbers(const vector<int>& primes) 
{
    for (int v : primes) {
        cout << v << endl;
    }
}

int main() 
{
    int num = 1;
    vector<int> primes;

    auto start_time = chrono::system_clock::now();

    vector<shared_ptr<thread> > threads;

    for (int i = 0; i < ThreadCount; i++) {
        shared_ptr<thread> thread(new thread([&]() {
            while (true) {
                int n;
                n = num;
                num++;

                if (n >= MaxCount)
                    break;

                if (IsPrimeNumber(n)) {
                    primes.push_back(n);
                }
            }
        }));
        threads.push_back(thread);
    }
    for (auto thread : threads)
    {
        thread->join();
    }

    auto end_time = chrono::system_clock::now();

    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Took" << duration << " milliseconds." << endl;

    // PrintNumbers(primes);

    return 0;
}

