// file to show use of thread and thread join

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

// function to print the thread id
void print_id(int id)
{
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "ID = " << id << endl;
}

int main()
{
    // create a vector to hold the threads
    vector<thread> threads;

    // launch 10 threads
    for (int i = 0; i < 10; ++i)
    {
        threads.push_back(thread(print_id, i));
    }

    // join the threads with the main thread
    for (auto &th : threads)
    {
        th.join();
    }

    return 0;
}