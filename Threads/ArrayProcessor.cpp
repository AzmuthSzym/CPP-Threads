#include "ArrayProcessor.h"

// Constructor
ArrayProcessor::ArrayProcessor(int* arr, int size, int numThreads)
    : arr(arr), size(size), numThreads(numThreads), threadSums(numThreads, 0) {}

// Destructor
ArrayProcessor::~ArrayProcessor() {
    // Join all threads before destruction
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

// Calculate sum using multiple threads
int ArrayProcessor::calculateSum() {
    // Divide the array into chunks for each thread
    int chunkSize = size / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        int startIndex = i * chunkSize;
        int endIndex = (i == numThreads - 1) ? size : (i + 1) * chunkSize;
        threads.emplace_back(&ArrayProcessor::threadWorker, this, startIndex, endIndex, i);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Aggregate sums from all threads
    int totalSum = 0;
    for (int sum : threadSums) {
        totalSum += sum;
    }
    return totalSum;
}

// Worker function for each thread
void ArrayProcessor::threadWorker(int startIndex, int endIndex, int threadIndex) {
    int threadSum = 0;
    for (int i = startIndex; i < endIndex; ++i) {
        threadSum += arr[i];
    }
    threadSums[threadIndex] = threadSum;
}