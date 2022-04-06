#include "Windows.h"
#include "fstream"
#include "ctime"

using namespace std;
int n;
static double ** M1;
static double ** M2;
static double ** result;
static ifstream fin("input.txt");
static ofstream fout("output.txt");

class parameters {
public:
    int ii;
    int kk;
    int jj;
    int block;
    parameters(int ii_, int kk_, int jj_, int block_) {
        ii = ii_;
        kk = kk_;
        jj = jj_;
        block = block_;
    }
};

void readFromFile(){
    fin >> n;
    M1 = new double * [n];
    M2 = new double * [n];
    result = new double * [n];
    for (int i = 0; i < n; i++) {
        M1[i] = new double[n];
        result[i] = new double [n];
        for (int j = 0; j < n; j++) {
            int el;
            fin >> el;
            M1[i][j] = el;
            result[i][j] = 0.;
        }
    }

    for (int i = 0; i < n; i++) {
        M2[i] = new double [n];
        for (int j = 0; j < n; j++) {
            int el;
            fin >> el;
            M2[i][j] = el;
        }
    }
}

void clearResult(){
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = 0.;
}

void printToFile(){
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fout << result[i][j] << " ";
        fout << "\n";
    }
    fout << "\n";
}

void __CLRCALL_PURE_OR_STDCALL deus_mult(LPVOID lpParam){
    auto* q = (parameters*) lpParam;
    double sum = 0.;
    int ii = q->ii, jj = q->jj, kk = q->kk, block = q->block;

    for (int i = ii; i < ii + block; i++)
        for (int j = jj; j < jj + block; j++) {
            for (int k = kk; k < kk + block; k++)
                sum += M1[i][k] * M2[k][j];

            HANDLE mtx = CreateMutex(nullptr, FALSE, nullptr);
            result[i][j] += sum;
            sum = 0.;
            ReleaseMutex(mtx);
        }
}

void ordinary_mult(){
    WaitForSingleObject(CreateThread(nullptr, 0,
                                     reinterpret_cast<LPTHREAD_START_ROUTINE>(&deus_mult),
                                     new parameters(0, 0, 0, n),
                                     0, nullptr), INFINITE);
}

void blocking_mult(int num){
    auto* handle = new HANDLE[pow(num, 3) + 20];
    int cou = 0;
    for (int ii = 0; ii < n; ii += n / num)
        for (int jj = 0; jj < n; jj += n / num)
            for (int kk = 0; kk < n; kk += n / num){
                handle[cou] = CreateThread(nullptr, 0,
                                           reinterpret_cast<LPTHREAD_START_ROUTINE>(&deus_mult),
                                           new parameters(ii, kk, jj, n / num),
                                           0, nullptr);
                cou++;
            }
    WaitForMultipleObjects(num, handle, true, INFINITE);
}

int main(){
    readFromFile();
    int f, s;
    f = clock();
    ordinary_mult();
    s = clock();
    fout  << "Ordinary:\n" << (s - f)/CLK_TCK << " s\n\n";
    printToFile();
    clearResult();


    for (int num = 1; num < n + 1; num++){
        if (n % num == 0) {
            f = clock();
            blocking_mult(num);
            s = clock();
            fout  << "Blocking:\nNum = " << num << " ; " << (s - f)/CLK_TCK << " s\n\n";
            printToFile();
            clearResult();
        }
    }
    return 0;
}