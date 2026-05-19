#include<iostream>
using namespace std;

struct process{
    int id, AT, BT, CT, TAT, WT, IT, priority, RT;
};

// ----------- FIXED INPUT -----------
void insert_process(process p[], int n){
    // Sample data (you can change)
    int AT[] = {0,1,2,3};
    int BT[] = {5,3,8,6};
    int PR[] = {2,1,3,2};

    for(int i=0;i<n;i++){
        p[i].id = i+1;
        p[i].AT = AT[i];
        p[i].BT = BT[i];
        p[i].priority = PR[i];
        p[i].RT = BT[i];
        p[i].IT = 0;
    }
}

// -------- DISPLAY -----------
void display(process p[], int n){
    float total_TAT=0, total_WT=0, total_IT=0;

    cout<<"\nP_ID\tAT\tBT\tCT\tTAT\tWT\tIT\n";
    for(int i=0;i<n;i++){
        cout<<p[i].id<<"\t"<<p[i].AT<<"\t"<<p[i].BT<<"\t"
            <<p[i].CT<<"\t"<<p[i].TAT<<"\t"<<p[i].WT<<"\t"<<p[i].IT<<endl;

        total_TAT+=p[i].TAT;
        total_WT+=p[i].WT;
        total_IT+=p[i].IT;
    }

    cout<<"\nAverage TAT: "<<total_TAT/n;
    cout<<"\nAverage WT: "<<total_WT/n;
    cout<<"\nAverage IT: "<<total_IT/n<<endl;
}

// -------- FCFS -----------
void fcfs(process p[], int n){
    int time=0;

    for(int i=0;i<n;i++){
        if(time < p[i].AT){
            p[i].IT = p[i].AT - time;
            time = p[i].AT;
        }

        time += p[i].BT;
        p[i].CT = time;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }

    cout<<"\n--- FCFS ---";
    display(p,n);
}

// -------- SJF NON PREEMPTIVE -----------
void sjf_non_preemptive(process p[], int n){
    bool done[10]={0};
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, minBT=9999;

        for(int i=0;i<n;i++){
            if(p[i].AT<=time && !done[i] && p[i].BT<minBT){
                minBT=p[i].BT;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        time += p[idx].BT;
        p[idx].CT = time;
        p[idx].TAT = p[idx].CT - p[idx].AT;
        p[idx].WT = p[idx].TAT - p[idx].BT;

        done[idx]=true;
        completed++;
    }

    cout<<"\n--- SJF (Non-Preemptive) ---";
    display(p,n);
}

// -------- SJF PREEMPTIVE -----------
void sjf_preemptive(process p[], int n){
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, minRT=9999;

        for(int i=0;i<n;i++){
            if(p[i].AT<=time && p[i].RT>0 && p[i].RT<minRT){
                minRT=p[i].RT;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        p[idx].RT--;
        time++;

        if(p[idx].RT==0){
            p[idx].CT=time;
            p[idx].TAT=p[idx].CT-p[idx].AT;
            p[idx].WT=p[idx].TAT-p[idx].BT;
            completed++;
        }
    }

    cout<<"\n--- SJF (Preemptive) ---";
    display(p,n);
}

// -------- ROUND ROBIN -----------
void round_robin(process p[], int n){
    int tq=2;
    int time=0, completed=0;

    while(completed<n){
        bool executed=false;

        for(int i=0;i<n;i++){
            if(p[i].AT<=time && p[i].RT>0){
                executed=true;

                if(p[i].RT>tq){
                    time += tq;
                    p[i].RT -= tq;
                }else{
                    time += p[i].RT;
                    p[i].RT=0;

                    p[i].CT=time;
                    p[i].TAT=p[i].CT-p[i].AT;
                    p[i].WT=p[i].TAT-p[i].BT;
                    completed++;
                }
            }
        }

        if(!executed) time++;
    }

    cout<<"\n--- Round Robin ---";
    display(p,n);
}

// -------- PRIORITY NON PREEMPTIVE -----------
void priority_non_preemptive(process p[], int n){
    bool done[10]={0};
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, best=9999;

        for(int i=0;i<n;i++){
            if(p[i].AT<=time && !done[i] && p[i].priority<best){
                best=p[i].priority;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        time += p[idx].BT;
        p[idx].CT=time;
        p[idx].TAT=p[idx].CT-p[idx].AT;
        p[idx].WT=p[idx].TAT-p[idx].BT;

        done[idx]=true;
        completed++;
    }

    cout<<"\n--- Priority (Non-Preemptive) ---";
    display(p,n);
}

// -------- PRIORITY PREEMPTIVE -----------
void priority_preemptive(process p[], int n){
    int time=0, completed=0;

    while(completed<n){
        int idx=-1, best=9999;

        for(int i=0;i<n;i++){
            if(p[i].AT<=time && p[i].RT>0 && p[i].priority<best){
                best=p[i].priority;
                idx=i;
            }
        }

        if(idx==-1){
            time++;
            continue;
        }

        p[idx].RT--;
        time++;

        if(p[idx].RT==0){
            p[idx].CT=time;
            p[idx].TAT=p[idx].CT-p[idx].AT;
            p[idx].WT=p[idx].TAT-p[idx].BT;
            completed++;
        }
    }

    cout<<"\n--- Priority (Preemptive) ---";
    display(p,n);
}

// -------- MAIN MENU -----------
int main(){
    int n=4, choice;

    do{
        process p[10];
        insert_process(p,n);

        cout<<"\n\n===== CPU Scheduling Menu =====";
        cout<<"\n1. FCFS";
        cout<<"\n2. SJF (Non-Preemptive)";
        cout<<"\n3. SJF (Preemptive)";
        cout<<"\n4. Round Robin";
        cout<<"\n5. Priority (Non-Preemptive)";
        cout<<"\n6. Priority (Preemptive)";
        cout<<"\n0. Exit";
        cout<<"\nEnter choice: ";
        cin>>choice;

        switch(choice){
            case 1: fcfs(p,n); break;
            case 2: sjf_non_preemptive(p,n); break;
            case 3: sjf_preemptive(p,n); break;
            case 4: round_robin(p,n); break;
            case 5: priority_non_preemptive(p,n); break;
            case 6: priority_preemptive(p,n); break;
        }

    }while(choice!=0);

    return 0;
}