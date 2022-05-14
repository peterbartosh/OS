#include <iostream>
#include <cstdlib>
#include "sstream"
#include <sys/wait.h>

using namespace std;

string path = "../../Killer/cmake-build-debug/Killer ";

pid_t get_pid(string & name){
    string str = "pidof " + name;
    char* line = new char[50];
    FILE *cmd = popen(str.c_str(), "r");
    fgets(line, 50, cmd);
    pid_t pid = strtoul(line, nullptr, 10);
    pclose(cmd);
    return pid;
}

void check(string & name){
    int pid;
    stringstream(name) >> pid;
    if (pid == 0) {
        pid = get_pid(name);
        if (kill(pid, 0) != -1) {
            cout << "WARNING!! (murder failed)\n";
            return;
        }
    } else {
        if (kill(pid, 0) != -1) {
            cout << "WARNING! (murder failed)\n";
            return;
        }
    }
}

void action(){
    string input;
    cin >> input;
    if (input == "kill"){
        string arg;
        cin >> arg;
        system((path + arg).c_str());
        check(arg);
        unsetenv("PROC_TO_KILL");
    } else if (input == "print"){
        system("ps -A");
    } else if (input == "exit"){
        return;
    } else {
        cout << "WARNING! (unknown command)\n";
    }
    action();
}

int main(){
    if (setenv("PROC_TO_KILL", "Telegram chrome ", 0) == -1)
        cout << "WARNING! (env var creation failed)\n";

    action();
    return 0;
}
