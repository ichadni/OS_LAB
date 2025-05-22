#include <iostream>
using namespace std;

void fcfsScheduling(int p[], int n, int bt[]) {
    int waitingTime[n], turnTime[n], totalWt = 0, totalTurn = 0;

    waitingTime[0] = 0;

    cout << endl;
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time" << endl;
    cout << "-------+-----------+--------------+------------------" << endl;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            waitingTime[i] = waitingTime[i - 1] + bt[i - 1];
        }
        totalWt += waitingTime[i];
        turnTime[i] = bt[i] + waitingTime[i];
        totalTurn += turnTime[i];

        cout << "P" << p[i] << "\t" << bt[i] << "\t\t" << waitingTime[i] << "\t\t" << turnTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWt / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurn / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int process[n], burstTime[n];
    for (int i = 0; i < n; i++) {
        cout << "Enter Process ID and Burst Time: ";
        cin >> process[i] >> burstTime[i];
    }

    fcfsScheduling(process, n, burstTime);
    return 0;
}
