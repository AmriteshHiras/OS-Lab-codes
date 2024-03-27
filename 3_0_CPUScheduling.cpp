#include <iostream>
using namespace std;

const int N = 100005;
int n;
struct process
{
    int PID;
    int AT;
    int BT;
    int RBT;
    int CT = 0;
    int TAT;
    int WT;
    int RT;
    int P;
};
process P[N];

void printTable(process P[], int n)
{
    cout << "\n-----------------------------------------------------------------------------------------------------------------\n";
    cout << "|\tPID\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|\tRT\t|\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    float turn_time = 0;
    float wait_time = 0;
    for (int i = 0; i < n; i++)
    {
        cout << "|\t " << P[i].PID << "\t|\t" << P[i].AT << "\t|\t" << P[i].BT << "\t|\t" << P[i].CT << "\t|\t " << P[i].TAT << "\t|\t" << P[i].WT << "\t|\t" << P[i].RT << "\t|\n";
        turn_time = turn_time + P[i].TAT;
        wait_time = wait_time + P[i].WT;
    }
    cout << "-----------------------------------------------------------------------------------------------------------------\n\n";
    cout << "Avg. Turn Around Time = " << turn_time / n << "\nAvg. Wait Time = " << wait_time / n << "\n\n\n";
}

void Sort_arrival(process P[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].AT > P[j].AT)
            {
                swap(P[i], P[j]);
            }
        }
    }
}

void deSort(process P[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].PID > P[j].PID)
            {
                swap(P[i], P[j]);
            }
        }
    }
}

// First Come First Serve Algorithm:-
void FCFS(process P[], int n)
{
    int time = 0;
    Sort_arrival(P, n);
    for (int i = 0; i < n; i++)
    {
        if (P[i].AT <= time)
        {
            time = time + P[i].BT;
            P[i].CT = time;
            P[i].TAT = P[i].CT - P[i].AT;
            P[i].WT = P[i].TAT - P[i].BT;
        }
        else
        {
            time = P[i].AT;
            time = time + P[i].BT;
            P[i].CT = time;
            P[i].TAT = P[i].CT - P[i].AT;
            P[i].WT = P[i].TAT - P[i].BT;
        }
    }
    deSort(P, n);
}

// Shortest Job First Algorithm:-
int *Sorted(process P[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].AT > P[j].AT)
            {
                swap(P[i], P[j]);
            }
        }
    }
    int *sorted_pid = new int[n];
    for (int i = 0; i < n; i++)
    {
        int ele = i;
        for (int j = 0; j < n; j++)
        {
            if (P[i].BT > P[j].BT && i < j)
            {
                ele++;
            }
            else if (P[i].BT < P[j].BT && i > j)
            {
                ele--;
            }
        }
        sorted_pid[ele] = P[i].PID;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].PID > P[j].PID)
            {
                swap(P[i], P[j]);
            }
        }
    }
    return sorted_pid;
}

void SJF(process P[], int n){
    int time = 0;
    int count = 0;
    int *SL = Sorted(P, n);
    int cycle = 0;
    while (count < n)
    {
        cycle = 0;
        for (int i = 0; i < n; i++)
        {
            if (P[SL[i] - 1].AT <= time && P[SL[i]- 1].CT == 0)
            {
                P[SL[i] - 1].CT = time + P[SL[i] - 1].BT;
                time += P[SL[i] - 1].BT;
                P[SL[i] - 1].TAT = P[SL[i] - 1].CT - P[SL[i] - 1].AT;
                P[SL[i] - 1].WT = P[SL[i] - 1].TAT - P[SL[i] - 1].BT;
                count++;
                cycle = 1;
                break;
            }
        }
        if (cycle == 0){
            time++;
        }
    }
}

// Round Robin Algorithm:-
void RR(process P[], int n)
{
    Sort_arrival(P, n);
    cout << "Enter Time Quantum: ";
    int TQ;
    cin >> TQ;
    int time = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        P[i].RBT = P[i].BT;
    }
    while (count != n)
    {
        int cycle = 0;
        for (int i = 0; i < n; i++)
        {
            cout << time << " P" << P[i].PID << " ";
            if (P[i].AT <= time && P[i].RBT != 0)
            {
                if (P[i].RBT == P[i].BT)
                {
                    P[i].RT = time - P[i].AT;
                };
                if (P[i].RBT > TQ)
                {
                    time += TQ;
                    P[i].RBT -= TQ;
                }
                else
                {
                    time += P[i].RBT;
                    P[i].RBT = 0;
                    P[i].CT = time;
                    P[i].TAT = P[i].CT - P[i].AT;
                    P[i].WT = P[i].TAT - P[i].BT;
                    count = count + 1;
                    cycle = 1;
                }
            }
        }
        if (cycle == 0)
        {
            time++;
        }
    }
}

// Priority Scheduling Algorithm(Pre-emptive):-
void Sort_prior(process P[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].AT > P[j].AT)
            {
                swap(P[i], P[j]);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].P < P[j].P)
            {
                swap(P[i], P[j]);
            }
        }
    }
}

void Priority(process P[], int n)
{
    int count = 0;
    int time = 0;
    int cycle;
    for (int i = 0; i < n; i++)
    {
        P[i].RBT = P[i].BT;
    }
    Sort_prior(P, n);
    while (count != n)
    {
        if (cycle == 0)
        {
            time++;
        }
        cycle = 0;
        for (int i = 0; i < n; i++)
        {
            if (P[i].AT <= time && P[i].RBT != 0)
            {
                if (P[i].BT == P[i].RBT)
                {
                    P[i].RT = time - P[i].AT;
                }
                time += 1;
                P[i].RBT -= 1;
                if (P[i].RBT == 0)
                {
                    count += 1;
                    P[i].CT = time;
                    P[i].TAT = P[i].CT - P[i].AT;
                    P[i].WT = P[i].TAT - P[i].BT;
                }
                cycle = 1;
                break;
            }
        }
    }
    deSort(P, n);
}

//SRJF Algorithm:-
void Sort_rbt(process P[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (P[i].RBT > P[j].RBT)
            {
                swap(P[i], P[j]);
            }
        }
    }
}

void SRJF(process P[], int n)
{
    int count = 0;
    int time = 0;
    int start = 0;
    Sort_rbt(P, n);
    for (int i = 0; i < n; i++)
    {
        P[i].RBT = P[i].BT;
    }
    while (count < n)
    {
        int cycle = 0;
        bool sjf = false;
        for (int i = 0; i < n; i++)
        {
            if (P[i].RBT != 0 && P[i].AT <= time)
            {
                cout << " For time " << time << " Executing " << P[i].PID << "\n";
                if (P[i].RBT == P[i].BT)
                {
                    P[i].RT = time - P[i].AT;
                    start++;
                    if (start == n)
                    {
                        sjf = true;
                    }
                }
                P[i].RBT -= 1;
                time++;
                if (P[i].RBT == 0)
                {
                    P[i].CT = time;
                    P[i].TAT = P[i].CT - P[i].AT;
                    P[i].WT = P[i].TAT - P[i].BT;
                    count++;
                }
                cycle++;
                Sort_rbt(P, n);
                break;
            }
        }
        if (sjf == true)
        {
            for (int i = 0; i < n; i++)
            {
                if (P[i].RBT != 0)
                {
                    cout << " For time " << time << " Executing " << P[i].PID << "\n";
                    time += P[i].RBT;
                    P[i].RBT = 0;
                    P[i].CT = time;
                    P[i].TAT = P[i].CT - P[i].AT;
                    P[i].WT = P[i].TAT - P[i].BT;
                    count++;
                }
            }
        }
        if (cycle == 0)
        {
            time++;
        }
    }
    deSort(P, n);
}

// Priority Scheduling Algorithm(Pre-emptive):-
void Priority_non(process P[], int n)
{
    int count = 0;
    int time = 0;
    Sort_prior(P, n);
    while (count < n)
    {
        int cycle = 0;
        for (int i = 0; i < n; i++)
        {
            if (P[i].AT <= time && P[i].CT == 0)
            {
                P[i].RT = time - P[i].AT;
                time += P[i].BT;
                P[i].CT = time;
                P[i].TAT = P[i].CT - P[i].AT;
                P[i].WT = P[i].TAT - P[i].BT;
                cycle = 1;
                count++;
                break;
            }
        }
        if (cycle == 0)
        {
            time++;
        }
    }
    deSort(P, n);
}

// Main Function:-
int main(){
    int n;
    int choice;
    cout << "1. FCFS\n2. SJf\n3. RoundRobin\n4. Priority Scheduling(Pre-emptive)\n5. SRJF \n6. Priority Scheduling(Non Pre-emptive)\n";
    cout << "Enter the algorithm:- ";
    cin >> choice;
    cout << "Enter the number of processes: ";
    cin >> n;
    process *P = new process[n];
    for (int i = 0; i < n; i++)
    {
        P[i].PID = i + 1;
        cout << "Enter AT for process " << i + 1 << ": ";
        cin >> P[i].AT;
        cout << "Enter BT for process " << i + 1 << ": ";
        cin >> P[i].BT;
        if(choice == 4 or choice == 6){
            cout << "Enter Priority order for process " << i + 1 << ": ";
            cin >> P[i].P;
        }
    }
    switch (choice){
        case 1:{
            cout << "FCFS outcome:-\n";
            FCFS(P, n);
            break;
        }
        case 2:{
            cout << "SJF outcome:-\n";
            SJF(P, n);
            break;
        }
        case 3:{
            cout << "Round Robin outcome:-\n";
            RR(P, n);
            break;
        }
        case 4:{
            cout << "Priority Scheduling(Pre-emptive) outcome:-\n";
            Priority(P, n);
            break;
        }
        case 5:{
            cout << "Shortest remaining job first outcome:-\n";
            SRJF(P, n);
            break;
        }
        case 6:{
            cout << "Priority Scheduling(Non Pre-emptive) outcome:-\n";
            Priority_non(P, n);
            break;
        }
        default:{
            cout << "Invalid Input!\n";
            break;
        }
    }
    printTable(P, n);
}
