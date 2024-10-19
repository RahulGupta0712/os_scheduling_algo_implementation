#include <iostream>
#include <algorithm>
using namespace std;

struct process
{
    int id, burstTime, arrivalTime;                  // given properties
    int waitingTime, completionTime, turnAroundTime; // to be found after scheduling

    process() {}

    process(int id, int burstTime, int arrivalTime)
    {
        this->id = id;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
    }
};

bool cmp(process &a, process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

int n;
process *jobs;

void input()
{
    cin >> n;

    jobs = new process[n];

    int id, burstTime, arrivalTime;
    for (int i = 0; i < n; ++i)
    {
        cin >> id >> arrivalTime >> burstTime;
        jobs[i] = process(id, burstTime, arrivalTime);
    }
}

void schedule()
{
    // FIRST COME FIRST SERVE
    // sort the processes on the basis of arrival time
    sort(jobs, jobs + n, cmp);

    int time = 0;

    for (int i = 0; i < n; ++i)
    {
        time += jobs[i].burstTime;
        jobs[i].completionTime = time;
        jobs[i].turnAroundTime = jobs[i].completionTime - jobs[i].arrivalTime;
        jobs[i].waitingTime = jobs[i].turnAroundTime - jobs[i].burstTime;
    }
}

void displayResult()
{
    cout << "ID\tA.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n";
    int totalWaitingTime = 0;
    for (int i = 0; i < n; ++i)
    {
        cout << jobs[i].id << "\t" << jobs[i].arrivalTime << "\t" << jobs[i].burstTime << "\t" << jobs[i].completionTime << "\t" << jobs[i].turnAroundTime << "\t" << jobs[i].waitingTime << "\n";
        totalWaitingTime += jobs[i].waitingTime;
    }
    double averageWaitingTime = totalWaitingTime / (n * 1.0);
    cout << "\nAverage Waiting Time : " << averageWaitingTime << "\n";
}

int main()
{
    input();
    schedule();
    displayResult();
    free(jobs);
    return 0;
}

/*
example :
    5
    1 0 4
    2 2 10
    3 1 12
    4 4 2
    5 4 1
*/