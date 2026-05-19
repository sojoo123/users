#include<iostream>

using namespace std;

// INTERRUPTS

int SI = 0;

int PI = 0;

int TI = 0;

// PCB VARIABLES

int TTC = 0;

int TTL = 50;

int LLC = 0;

int TLL = 10;

// TERMINATE FUNCTION

void terminate(int error)
{
    switch(error)
    {
        case 0:
            cout<<"NO ERROR";
            break;

        case 1:
            cout<<"OUT OF DATA";
            break;

        case 2:
            cout<<"LINE LIMIT EXCEEDED";
            break;

        case 3:
            cout<<"TIME LIMIT EXCEEDED";
            break;

        case 4:
            cout<<"OPCODE ERROR";
            break;

        case 5:
            cout<<"OPERAND ERROR";
            break;

        case 6:
            cout<<"INVALID PAGE FAULT";
            break;
    }

    cout<<endl;
}

// PAGE FAULT HANDLER

void handlePageFault()
{
    cout<<"VALID PAGE FAULT"<<endl;

    cout<<"NEW FRAME ALLOCATED"<<endl;

    PI = 0;
}

// MOS FUNCTION

void mos(string op)
{
    // OPCODE ERROR

    if(TI==0 && PI==1)
    {
        terminate(4);
    }

    // OPERAND ERROR

    else if(TI==0 && PI==2)
    {
        terminate(5);
    }

    // PAGE FAULT

    else if(TI==0 && PI==3)
    {
        // VALID PAGE FAULT

        if(op=="GD" ||
           op=="SR")
        {
            handlePageFault();
        }
        else
        {
            terminate(6);
        }
    }

    // TIME LIMIT

    else if(TI==2)
    {
        terminate(3);
    }

    // SERVICE INTERRUPTS

    else if(SI==1)
    {
        cout<<"READ OPERATION"<<endl;
    }

    else if(SI==2)
    {
        LLC++;

        if(LLC > TLL)
        {
            terminate(2);
        }
        else
        {
            cout<<"WRITE OPERATION"<<endl;
        }
    }

    else if(SI==3)
    {
        cout<<"PROGRAM HALTED"<<endl;
    }
}

int main()
{
    int choice;

    while(true)
    {
        cout<<"\n===== MOS PHASE 2 =====\n";

        cout<<"1. Opcode Error\n";

        cout<<"2. Operand Error\n";

        cout<<"3. Valid Page Fault\n";

        cout<<"4. Invalid Page Fault\n";

        cout<<"5. Time Limit Exceeded\n";

        cout<<"6. Line Limit Exceeded\n";

        cout<<"7. GD Instruction\n";

        cout<<"8. PD Instruction\n";

        cout<<"9. Halt\n";

        cout<<"10. Exit\n";

        cin>>choice;

        // RESET

        SI = PI = TI = 0;

        switch(choice)
        {
            case 1:

                PI = 1;

                mos("");

                break;

            case 2:

                PI = 2;

                mos("");

                break;

            case 3:

                PI = 3;

                mos("GD");

                break;

            case 4:

                PI = 3;

                mos("LR");

                break;

            case 5:

                TTC = 60;

                if(TTC > TTL)
                {
                    TI = 2;
                }

                mos("");

                break;

            case 6:

                LLC = 11;

                SI = 2;

                mos("");

                break;

            case 7:

                SI = 1;

                mos("");

                break;

            case 8:

                SI = 2;

                mos("");

                break;

            case 9:

                SI = 3;

                mos("");

                break;

            case 10:

                return 0;

            default:

                cout<<"INVALID CHOICE";
        }
    }

    return 0;
}