#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    if (remove("file1.txt") == 0)
        cout << "File deleted successfully.\n";
    else
        perror("Error deleting file");
    return 0;
}
