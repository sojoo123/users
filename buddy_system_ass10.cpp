#include <iostream>
#include <vector>
using namespace std;

// Function to find next power of 2
int nextPowerOf2(int n)
{
    int p = 1;

    while (p < n)
        p *= 2;

    return p;
}

int main()
{
    int memorySize, n;

    cout << "Enter Total Memory Size (KB): ";
    cin >> memorySize;

    cout << "Enter Number of Processes: ";
    cin >> n;

    vector<int> process(n);

    for (int i = 0; i < n; i++)
    {
        cout << "Enter memory required for Process P" << i + 1 << ": ";
        cin >> process[i];
    }

    int remainingMemory = memorySize;

    cout << "\n========== Buddy System Allocation ==========\n";

    for (int i = 0; i < n; i++)
    {
        cout << "\nProcess P" << i + 1 << " requesting "
             << process[i] << " KB\n";

        int requiredBlock = nextPowerOf2(process[i]);

        cout << "Nearest Power of 2 Block: "
             << requiredBlock << " KB\n";

        if (requiredBlock > remainingMemory)
        {
            cout << "Allocation FAILED (Insufficient Memory)\n";
            continue;
        }

        // Show splitting process
        int currentBlock = memorySize;

        cout << "Splitting Process:\n";

        while (currentBlock / 2 >= requiredBlock)
        {
            cout << currentBlock
                 << " KB -> "
                 << currentBlock / 2
                 << " KB + "
                 << currentBlock / 2
                 << " KB\n";

            currentBlock /= 2;
        }

        cout << "Allocated Block: "
             << currentBlock << " KB\n";

        cout << "Internal Fragmentation: "
             << currentBlock - process[i]
             << " KB\n";

        remainingMemory -= currentBlock;

        cout << "Remaining Memory: "
             << remainingMemory
             << " KB\n";
    }

    cout << "\n========== Allocation Finished ==========\n";

    return 0;
}