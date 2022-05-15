#include <iostream>
#include <unistd.h>

using namespace std;

typedef const char* cc;

cc P_path = "../../P/cmake-build-debug/P";
cc A_path = "../../A/cmake-build-debug/A";
cc M_path = "../../M/cmake-build-debug/M";
cc S_path = "../../S/cmake-build-debug/S";

int* pipes = new int[3];

int run(cc & path){
    pipe(pipes);

    if (!fork()) {
        if (dup2(pipes[1], 1) == -1) return -1;
        system(path);
        return 0;
    }
    if (dup2(pipes[0], 0) == -1) return -1;
}

int main() {
    printf("enter start data:\n");
    if (run(P_path) == 0)
        if (run(A_path) == 0)
            if (run(M_path) == 0)
                system(S_path);

    return 0;
}