// ProducerConsumer.cpp
//

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

//Another exercise where one thread produces data and the other one consumes it sharing one data structure

queue<int> dataQueue;
mutex mtx;
condition_variable cv;

void producer()
{
    for (int i = 0; i < 10; i++)
    {
        int newElement = i;

        unique_lock<mutex> lock(mtx);
        dataQueue.push(newElement);

        cout << "Added an element: " << newElement << endl;

        cv.notify_one();
        lock.unlock();

        //Delay just to simulate processing time
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void consumer()
{
    for (int i = 0; i < 10; i++)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] {return !dataQueue.empty(); });

        int data = dataQueue.front();
        dataQueue.pop();
        cout << "Taken element: " << data << endl;

        lock.unlock();

        //Delay just to simulate processing time
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main()
{
    thread producerThread(producer), consumerThread(consumer);
    producerThread.join();
    consumerThread.join();

    system("pause");
    return 0;
}