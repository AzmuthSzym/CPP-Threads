#include "pch.h"
#include "../Threads/ArrayProcessor.h"

// Test fixture for ArrayProcessor class
class ArrayProcessorTest : public ::testing::Test {
protected:
    // Test setup
    void SetUp() override {
        // Initialize the array with values 1, 2, 3, ..., arrSize
        for (int i = 0; i < arrSize; ++i) {
            arr[i] = i + 1;
        }
    }

    // Test teardown
    void TearDown() override {}

    // Constants for test
    static const int arrSize = 1000000;  // Size of the array
    int arr[arrSize];  // Array to be processed
};

// Test case to verify ArrayProcessor constructor
/*TEST_F(ArrayProcessorTest, ConstructorTest) {
    ArrayProcessor processor(arr, arrSize, 4);

    // Check if the object is constructed successfully
    EXPECT_TRUE(true);  // Placeholder for now, modify as needed
}*/

// Test case to verify ArrayProcessor calculateSum method
TEST_F(ArrayProcessorTest, CalculateSumTest) {
    ArrayProcessor processor(arr, arrSize, 4);

    // Calculate sum using multiple threads
    int sum = processor.calculateSum();

    // Calculate expected sum (sum of 1, 2, 3, ..., arrSize)
    long long expectedSum = (long long)arrSize * (arrSize + 1) / 2;

    // Check if the calculated sum matches the expected sum
    EXPECT_EQ(sum, expectedSum);
}

// Additional test cases can be added as needed

int main(int argc, char** argv) {
    // Initialize Google Test framework
    ::testing::InitGoogleTest(&argc, argv);

    // Run tests
    return RUN_ALL_TESTS();
}