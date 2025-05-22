#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "Fork failed.\n";
        return 1;
    }
    else if (pid == 0) {
        std::cout << "Child process (PID: " << getpid() << ") created.\n";
        execlp("/bin/ls", "ls", "-l", NULL);
        std::cerr << "execlp failed.\n";
        return 1;
    }
    else {
        std::cout << "Parent process (PID: " << getpid() << "), child PID: " << pid << "\n";
        wait(NULL);
        std::cout << "Child process finished and deleted.\n";
    }

    return 0;
}
