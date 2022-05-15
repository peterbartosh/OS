#include <iostream>
#include "sstream"

using namespace std;

int main() {
    string str, token, res;
    getline(cin, str);
    stringstream ss(str);

    while (ss >> token) {
        int tmp = stoi(token, nullptr, 10);
        res.append(to_string(tmp*7) + " ");
    }
    cout << res << "\n";
    return 0;
}