#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "vector"
#include "algorithm"

using namespace std;

void kill_envir_args() {
    char* arg = getenv("PROC_TO_KILL");
    if (arg == nullptr) return;
    string input(arg);
    while (!input.empty()) {
        auto end = find(input.begin(), input.end(), ' ');
        string tmp = input.substr(0, end - input.begin());
        if (end == input.end()) break;
        end++;
        input.erase(input.begin(), end);
        system(("killall " + tmp).c_str());
    }
}

void kill(char* arg){
    kill_envir_args();
    string name(arg);
    int pid;
    stringstream(name) >> pid;

    if (pid == 0)
        system(("killall " + name).c_str());
    else
        system(("kill " + to_string(pid)).c_str());

}


int main(int argc, char* argv[]) {
    if (argc == 2)
        kill(argv[1]);
    else
        cout << "WARNING! (must enter 2 args)\n";
    return 0;
}