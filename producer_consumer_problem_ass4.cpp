#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>

using namespace std;

const int BUFFER_SIZE = 5;
queue<int> buffer;

mutex mtx;
condition_variable cv;

int item = 1; // shared item counter

void producer(int id) {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(item);
        cout << "Producer " << id << " produced: " << item << endl;
        item++;

        cv.notify_all();
    }
}

void consumer(int id) {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);

        cv.wait(lock, [] { return !buffer.empty(); });

        int val = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << val << endl;

        cv.notify_all();
    }
}

int main() {
    int p, c;

    cout << "Enter number of producers: ";
    cin >> p;

    cout << "Enter number of consumers: ";
    cin >> c;

    vector<thread> producers, consumers;

    // create producer threads
    for (int i = 0; i < p; i++) {
        producers.push_back(thread(producer, i + 1));
    }

    // create consumer threads
    for (int i = 0; i < c; i++) {
        consumers.push_back(thread(consumer, i + 1));
    }

    // join all threads
    for (auto &t : producers) t.join();
    for (auto &t : consumers) t.join();

    return 0;
}