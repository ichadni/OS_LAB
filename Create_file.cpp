#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream file("file1.txt");
    if (file.is_open()) {
        file << "Hello, this is a test file.\n";
        file.close();
        cout << "File created successfully.\n";
    } else {
        cout << "Unable to create file.\n";
    }
    return 0;
}
