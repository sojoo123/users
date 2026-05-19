#include<iostream>
#include<vector>
using namespace std;

void firstFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nFirst Fit:\n";
    for(int i=0;i<n;i++) {
        if(allocation[i] != -1)
            cout << "Process " << i << " -> Block " << allocation[i] << endl;
        else
            cout << "Process " << i << " -> Not Allocated\n";
    }
}


void bestFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for(int i=0;i<n;i++) {
        int bestIdx = -1;
        for(int j=0;j<m;j++) {
            if(blockSize[j] >= processSize[i]) {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx])
                    bestIdx = j;
            }
        }

        if(bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nBest Fit:\n";
    for(int i=0;i<n;i++) {
        if(allocation[i] != -1)
            cout << "Process " << i << " -> Block " << allocation[i] << endl;
        else
            cout << "Process " << i << " -> Not Allocated\n";
    }
}

void worstFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    for(int i=0;i<n;i++) {
        int worstIdx = -1;
        for(int j=0;j<m;j++) {
            if(blockSize[j] >= processSize[i]) {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        if(worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }

    cout << "\nWorst Fit:\n";
    for(int i=0;i<n;i++) {
        if(allocation[i] != -1)
            cout << "Process " << i << " -> Block " << allocation[i] << endl;
        else
            cout << "Process " << i << " -> Not Allocated\n";
    }
}

void nextFit(vector<int> blockSize, int m, vector<int> processSize, int n) {
    vector<int> allocation(n, -1);

    int j = 0;

    for(int i=0;i<n;i++) {
        int count = 0;

        while(count < m) {
            if(blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
            j = (j + 1) % m;
            count++;
        }
    }

    cout << "\nNext Fit:\n";
    for(int i=0;i<n;i++) {
        if(allocation[i] != -1)
            cout << "Process " << i << " -> Block " << allocation[i] << endl;
        else
            cout << "Process " << i << " -> Not Allocated\n";
    }
}

int main() {
    int m, n;

    cout << "Enter number of memory blocks: ";
    cin >> m;

    vector<int> blockSize(m);
    cout << "Enter block sizes:\n";
    for(int i=0;i<m;i++)
        cin >> blockSize[i];

    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> processSize(n);
    cout << "Enter process sizes:\n";
    for(int i=0;i<n;i++)
        cin >> processSize[i];

    // Copy arrays for each algorithm
    vector<int> b1 = blockSize;
    vector<int> b2 = blockSize;
    vector<int> b3 = blockSize;
    vector<int> b4 = blockSize;

    firstFit(b1, m, processSize, n);
    bestFit(b2, m, processSize, n);
    nextFit(b3, m, processSize, n);
    worstFit(b4, m, processSize, n);

    return 0;
}