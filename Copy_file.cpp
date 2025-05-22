#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream src("file2.txt", ios::binary);
    ofstream dst("copied_file.txt", ios::binary);

    if (!src || !dst) {
        cerr << "Error opening files.\n";
        return 1;
    }

    dst << src.rdbuf();  // Copy content
    cout << "File copied successfully.\n";
    return 0;
}
