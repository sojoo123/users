#include <iostream>
using namespace std;

#define MAX 10

int n, m; // n = processes, m = resources

// Banker’s Algorithm
void bankersAlgorithm(int alloc[10][10], int max[MAX][MAX], int avail[MAX]) {
    int need[MAX][MAX], finish[MAX] = {0}, safeSeq[MAX];
    int work[MAX];

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize work = available
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is NOT in safe state (Deadlock possible)\n";
            return;
        }
    }

    cout << "\nSystem is in SAFE state\nSafe sequence: ";
    for (int i = 0; i < n; i++)
        cout << "P" << safeSeq[i] << " ";
    cout << endl;
}

// Deadlock Detection Algorithm
void deadlockDetection(int alloc[MAX][MAX], int request[MAX][MAX], int avail[MAX]) {
    int work[MAX], finish[MAX] = {0};

    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    while (true) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j])
                        break;
                }

                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found)
            break;
    }

    int deadlock = 0;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            cout << "Process P" << i << " is in deadlock\n";
            deadlock = 1;
        }
    }

    if (!deadlock)
        cout << "No deadlock detected\n";
}

int main() {
    int alloc[MAX][MAX], max[MAX][MAX], avail[MAX], request[MAX][MAX];

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    bankersAlgorithm(alloc, max, avail);

    cout << "\nEnter Request Matrix (for Deadlock Detection):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> request[i][j];

    deadlockDetection(alloc, request, avail);

    return 0;
}