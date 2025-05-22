#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    if (rename("copied_file.txt", "moved_file.txt") == 0)
        cout << "File moved/renamed successfully.\n";
    else
        perror("Error moving file");
    return 0;
}
