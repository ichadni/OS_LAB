#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the ID, Burst Time, and Priority for Process " << i + 1 << ": ";
        cin >> processes[i].id >> processes[i].burstTime >> processes[i].priority;
    }

    // Sort processes by descending priority (higher priority first)
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority > b.priority;
    });

    vector<int> waitingTime(n);
    vector<int> turnaroundTime(n);

    waitingTime[0] = 0;
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }

    cout << "\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].priority << "\t\t"
             << waitingTime[i] << "\t\t"
             << turnaroundTime[i] << endl;
    }

    return 0;
}
