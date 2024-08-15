#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    string input_file = argv[1];
    ifstream file(input_file);
    string str;
    while(getline(file, str)) {
        cout << str << endl;
    }
    return 0;
}