#pragma once
#include <iostream>
#include <vector>
#include <thread>

class ArrayProcessor {
public:
    // Constructor
    ArrayProcessor(int* arr, int size, int numThreads);

    // Destructor
    ~ArrayProcessor();

    // Calculate sum using multiple threads
    int calculateSum();

private:
    int* arr;
    int size;
    int numThreads;
    std::vector<std::thread> threads;
    std::vector<int> threadSums;

    // Worker function for each thread
    void threadWorker(int startIndex, int endIndex, int threadIndex);
};

