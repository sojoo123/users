#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
int N, cycles;
mutex *forks;
mutex printMutex;

void think(int id)
{
    {
        lock_guard<mutex> lock(printMutex);
        cout << "Philosopher " << id << " is thinking\n";
    }
    this_thread::sleep_for(chrono::seconds(1));
}

void eat(int id)
{
    {
        lock_guard<mutex> lock(printMutex);
        cout << "Philosopher " << id << " is eating\n";
    }
    this_thread::sleep_for(chrono::seconds(1));
}

void philosopher(int id)
{
    for (int i = 0; i < cycles; i++)
    {
        think(id);

        if (id % 2 == 0)
        {
            forks[id].lock();
            forks[(id + 1) % N].lock();
        }
        else
        {
            forks[(id + 1) % N].lock();
            forks[id].lock();
        }

        eat(id);

        forks[id].unlock();
        forks[(id + 1) % N].unlock();
    }
}

int main()
{
    cout << "Enter number of philosophers: ";
    cin >> N;

    cout << "Enter number of cycles: ";
    cin >> cycles;

    forks = new mutex[N];
    thread *philosophers = new thread[N]; // ✅ FIXED

    for (int i = 0; i < N; i++)
    {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < N; i++)
    {
        philosophers[i].join();
    }

    delete[] forks;
    delete[] philosophers; // cleanup

    return 0;
}