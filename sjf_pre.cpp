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
        allocatedTime = 0;
    }
};

bool cmp(process &a, process &b)
{
    return a.arrivalTime < b.arrivalTime;
}

class cmp2
{
public:
    bool operator()(process *a, process *b)
    {
        return b->burstTime < a->burstTime;
    }
};

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
    // SHORTEST JOB FIRST [PREEMPTIVE]

    // sort the processes on the basis of arrival time
    sort(jobs, jobs + n, cmp);

    // take the job with minimum burst time at every second
    priority_queue<process *, vector<process *>, cmp2> minHeap;

    int time = jobs[0].arrivalTime;
    
    int lastAddedProcess = -1;
    for (int i = 0; i < n; ++i)
    {
        if (jobs[i].arrivalTime <= time)
        {
            minHeap.push(&jobs[i]);
            lastAddedProcess = i;
        }
        else
        {
            break;
        }
    }

    while (!minHeap.empty())
    {
        process *scheduledProcess = minHeap.top();
        minHeap.pop();

        time += 1;
        scheduledProcess->allocatedTime += 1;

        if (scheduledProcess->burstTime == scheduledProcess->allocatedTime)
        {
            // process is completed and ready to terminate
            scheduledProcess->completionTime = time;
            scheduledProcess->turnAroundTime = scheduledProcess->completionTime - scheduledProcess->arrivalTime;
            scheduledProcess->waitingTime = scheduledProcess->turnAroundTime - scheduledProcess->burstTime;
        }
        else
        {
            // process is remaining
            minHeap.push(scheduledProcess);
        }

        for (int i = lastAddedProcess + 1; i < n; ++i)
        {
            if (jobs[i].arrivalTime <= time)
            {
                minHeap.push(&jobs[i]);
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


5
1 0 4
2 0 2
3 1 12
4 2 1
5 3 1
*/