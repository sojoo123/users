#include <iostream>
using namespace std;

// ---------------- PAGING ----------------
void paging()
{
    int pageSize, logicalAddress;
    int pageNumber, offset;
    int frameNumber;

    cout << "\n===== PAGING =====\n";

    cout << "Enter Page Size: ";
    cin >> pageSize;

    cout << "Enter Logical Address: ";
    cin >> logicalAddress;

    // Calculate page number and offset
    pageNumber = logicalAddress / pageSize;
    offset = logicalAddress % pageSize;

    cout << "Page Number: " << pageNumber << endl;
    cout << "Offset: " << offset << endl;

    // User provides frame number
    cout << "Enter Frame Number for Page "
         << pageNumber << ": ";
    cin >> frameNumber;

    int physicalAddress =
        frameNumber * pageSize + offset;

    cout << "Physical Address: "
         << physicalAddress << endl;
}

// ---------------- SEGMENTATION ----------------
void segmentation()
{
    int segmentNumber;
    int offset;
    int base, limit;

    cout << "\n===== SEGMENTATION =====\n";

    cout << "Enter Segment Number: ";
    cin >> segmentNumber;

    cout << "Enter Offset: ";
    cin >> offset;

    cout << "Enter Base Address of Segment "
         << segmentNumber << ": ";
    cin >> base;

    cout << "Enter Limit of Segment "
         << segmentNumber << ": ";
    cin >> limit;

    // Check validity
    if (offset < limit)
    {
        int physicalAddress = base + offset;

        cout << "Physical Address: "
             << physicalAddress << endl;
    }
    else
    {
        cout << "Segmentation Fault!\n";
    }
}

// ---------------- MAIN ----------------
int main()
{
    paging();

    segmentation();

    return 0;
}