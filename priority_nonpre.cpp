#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct process
{
    int id, burstTime, arrivalTime, priority;        // given properties
    int waitingTime, completionTime, turnAroundTime; // to be found after scheduling

    // higher the number, higher the priority

    process() {}

    process(int id, int burstTime, int arrivalTime, int priority)
    {
        this->id = id;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->priority = priority;
    }
};

bool cmp(process &a, process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

class cmp2
{
public:
    bool operator()(process *below, process *above)
    {
        return above->priority > below->priority;
    }
};

int n;
process *jobs;

void input()
{
    cin >> n;

    jobs = new process[n];

    int id, burstTime, arrivalTime, priority;
    for (int i = 0; i < n; ++i)
    {
        cin >> id >> priority >> arrivalTime >> burstTime;
        jobs[i] = process(id, burstTime, arrivalTime, priority);
    }
}

void schedule()
{
    // PRIORITY SCHEDULING [NON-PREEMPTIVE]

    // sort the processes on the basis of arrival time
    sort(jobs, jobs + n, cmp);

    // take the job with highest priority
    priority_queue<process *, vector<process *>, cmp2> maxHeap;
    maxHeap.push(&jobs[0]);

    int time = 0;

    int lastAddedProcess = 0;

    while (!maxHeap.empty())
    {
        process* scheduledProcess = maxHeap.top();
        maxHeap.pop();

        time += scheduledProcess->burstTime;
        scheduledProcess->completionTime = time;
        scheduledProcess->turnAroundTime = scheduledProcess->completionTime - scheduledProcess->arrivalTime;
        scheduledProcess->waitingTime = scheduledProcess->turnAroundTime - scheduledProcess->burstTime;

        for (int i = lastAddedProcess + 1; i < n; ++i)
        {
            if (jobs[i].arrivalTime <= time)
            {
                maxHeap.push(&jobs[i]);
                lastAddedProcess = i;
            }
            else
            {
                break;
            }
        }
    }
}

void displayResult()
{
    cout << "ID   Priority  A.T.\tB.T.\tC.T.\tT.A.T.\tW.T.\n";
    int totalWaitingTime = 0;
    for (int i = 0; i < n; ++i)
    {
        cout << jobs[i].id << "\t" << jobs[i].priority << "\t" << jobs[i].arrivalTime << "\t" << jobs[i].burstTime << "\t" << jobs[i].completionTime << "\t" << jobs[i].turnAroundTime << "\t" << jobs[i].waitingTime << "\n";
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
    1 3 0 4
    2 10 2 10
    3 2 1 12
    4 8 2 1
    5 9 15 1
*/