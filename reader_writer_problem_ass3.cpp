#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

using namespace std;

int read_count = 0;

mutex mtx;
mutex wrt;           // replaces semaphore
mutex print_mutex;

void reader(int id) {

    mtx.lock();
    read_count++;

    if (read_count == 1)
        wrt.lock();   // first reader blocks writers

    mtx.unlock();

    // Critical section
    print_mutex.lock();
    cout << "Reader " << id << " is reading" << endl;
    print_mutex.unlock();

    this_thread::sleep_for(chrono::seconds(1));

    mtx.lock();
    read_count--;

    if (read_count == 0)
        wrt.unlock(); // last reader releases writer

    mtx.unlock();
}

void writer(int id) {

    wrt.lock();

    print_mutex.lock();
    cout << "Writer " << id << " is writing" << endl;
    print_mutex.unlock();

    this_thread::sleep_for(chrono::seconds(2));

    wrt.unlock();
}

int main() {

    int r, w;

    cout << "Enter number of Readers: ";
    cin >> r;

    cout << "Enter number of Writers: ";
    cin >> w;

    vector<thread> readers, writers;

    for (int i = 0; i < r; i++)
        readers.push_back(thread(reader, i + 1));

    for (int i = 0; i < w; i++)
        writers.push_back(thread(writer, i + 1));

    for (auto &t : readers)
        t.join();

    for (auto &t : writers)
        t.join();

    return 0;
}