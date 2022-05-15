#include <iostream>
#include "sstream"

using namespace std;

int main() {
    int sum = 0;
    string str, token;
    getline(cin, str);
    stringstream ss(str);

    while (ss >> token) {
        int tmp = stoi(token, nullptr, 10);
        sum += tmp;
    }
    cout << sum << "\n";

    return 0;
}