// This file creates a simple thread

#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void *threadFunction(void *arg)
{
    // printing argument
    cout << "File name: " << (char *)arg << endl;
    ifstream file;
    file.open((char *)arg, ios::in);
    if (!file)
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    // creating vector to store numbers
    vector<int> numbers;

    // reading a line from file
    string line;
    while (getline(file, line))
    {
        // checking if first character is - sign
        if (line[0] != '-')
        {
            // converting string to integer
            int num = stoi(line);
            // storing in vector if unique
            if (find(numbers.begin(), numbers.end(), num) == numbers.end())
            {
                numbers.push_back(num);
            }
        }
    }
    file.close();

    // converting vector to dynamic integer array
    int *arr = new int[numbers.size()];
    for (int i = 0; i < numbers.size(); i++)
    {
        arr[i] = numbers[i];
    }

    // returning vector by pthread_exit
    pthread_exit((void *)arr);
}

// using pthread_create
int main()
{
    pthread_t thread1;
    char *message1 = "f1.txt";
    pthread_create(&thread1, NULL, *threadFunction, message1);
    void *ret;
    pthread_join(thread1, &ret);
    int *arr = (int *)ret;

    // printing array by for loop
    int sum = 0;
    int i = 0;
    for (i = 0; arr[i] != 0; i++)
    {
        sum += arr[i];
    }
    cout << "Average of numbers: " << sum / i << endl;
    return 0;
}