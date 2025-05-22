#include <iostream>
#include <algorithm>
using namespace std;

struct process {
    int pid, arrivalTime, burstTime, waitingTime, completionTime, turnAroundTime;
};

int main() {
    int n;
    float awt = 0, atat = 0;

    cout << "Enter the number of processes: ";
    cin >> n;

    process p[n];

    // Input arrival time and burst time for each process
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Enter arrival time for process P" << p[i].pid << ": ";
        cin >> p[i].arrivalTime;
        cout << "Enter burst time for process P" << p[i].pid << ": ";
        cin >> p[i].burstTime;
    }

    // Sort processes by arrival time; if tie, by burst time
    sort(p, p + n, [](process a, process b) {
        if (a.arrivalTime == b.arrivalTime) {
            return a.burstTime < b.burstTime;
        }
        return a.arrivalTime < b.arrivalTime;
    });

    // Calculate waiting time for each process
    p[0].waitingTime = 0;
    for (int i = 1; i < n; i++) {
        int totalBurst = 0;
        for (int j = 0; j < i; j++) {
            totalBurst += p[j].burstTime;
        }
        p[i].waitingTime = totalBurst - (p[i].arrivalTime - p[0].arrivalTime);
        if (p[i].waitingTime < 0) p[i].waitingTime = 0;  // waiting time cannot be negative
    }

    // Calculate completion time for each process
    p[0].completionTime = p[0].arrivalTime + p[0].burstTime;
    for (int i = 1; i < n; i++) {
        p[i].completionTime = max(p[i].arrivalTime, p[i - 1].completionTime) + p[i].burstTime;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        p[i].turnAroundTime = p[i].completionTime - p[i].arrivalTime;
    }

    // Calculate average waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        awt += p[i].waitingTime;
        atat += p[i].turnAroundTime;
    }
    awt /= n;
    atat /= n;

    // Print results
    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tCompletion Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].pid << "\t\t" << p[i].arrivalTime << "\t\t" << p[i].burstTime << "\t\t" 
             << p[i].waitingTime << "\t\t" << p[i].completionTime << "\t\t" << p[i].turnAroundTime << "\n";
    }

    cout << "\nAverage Waiting Time: " << awt << endl;
    cout << "Average Turnaround Time: " << atat << endl;

    return 0;
}
