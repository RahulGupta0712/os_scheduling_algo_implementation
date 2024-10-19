#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct process
{
    int id, burstTime, arrivalTime;                                 // given properties
    int waitingTime, completionTime, turnAroundTime, allocatedTime; // to be found after scheduling

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
    // ROUND ROBIN SCHEDULING

    int timeQuantum = 2;

    // sort the processes on the basis of arrival time
    sort(jobs, jobs + n, cmp);

    queue<process *> q;
    q.push(&jobs[0]);

    int lastAddedProcess = 0;
    int time = 0;

    while (!q.empty())
    {
        process *scheduledProcess = q.front();
        q.pop();

        int remainingTime = scheduledProcess->burstTime - scheduledProcess->allocatedTime;
        if (remainingTime > timeQuantum)
        {
            scheduledProcess->allocatedTime += timeQuantum;
            time += timeQuantum;
        }
        else
        {
            scheduledProcess->allocatedTime += remainingTime;
            time += remainingTime;
        }

        for (int i = lastAddedProcess + 1; i < n; ++i)
        {
            if (jobs[i].arrivalTime <= time)
            {
                q.push(&jobs[i]);
                lastAddedProcess = i;
            }
            else
            {
                break;
            }
        }

        if (scheduledProcess->allocatedTime < scheduledProcess->burstTime)
        {
            // if process is remaining
            q.push(scheduledProcess);
        }
        else
        {
            // process completed
            scheduledProcess->completionTime = time;
            scheduledProcess->turnAroundTime = scheduledProcess->completionTime - scheduledProcess->arrivalTime;
            scheduledProcess->waitingTime = scheduledProcess->turnAroundTime - scheduledProcess->burstTime;
        }
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
    4 2 1
    5 3 1
*/
