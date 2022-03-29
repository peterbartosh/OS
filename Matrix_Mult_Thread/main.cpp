#include "thread"
#include "mutex"
#include "iostream"
#include "fstream"
#include "list"

using namespace std;

int n;
static double ** M1;
static double ** M2;
static double ** result;
static ifstream fin("input.txt");
static ofstream fout("output.txt");

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

void mult(int ii, int kk, int jj, int block){
    mutex mtx; double sum = 0.;
    for (int i = ii; i < ii + block; i++)
        for (int j = jj; j < jj + block; j++) {
            for (int k = kk; k < kk + block; k++)
                sum += M1[i][k] * M2[ k][j];
            mtx.lock();
            result[i][j] += sum;
            mtx.unlock();
            sum = 0.;
        }
}

void ordinary_mult(){
    thread thr(mult, 0, 0, 0, n);
    thr.join();
}

void blocking_mult(int num){
    list<thread> list;
    for (int ii = 0; ii < n; ii += n / num)
        for (int jj = 0; jj < n; jj += n / num)
            for (int kk = 0; kk < n; kk += n / num){
                thread thr(mult, ii, kk, jj, n / num);
                list.push_back(move(thr));
            }
    for (auto item = list.begin(); item != list.end(); item++) item->join();
}

int main(){
    srand(time(0));
    readFromFile();
    int f, s;
    f = clock();
    ordinary_mult();
    s = clock();
    fout  << "Ordinary:\n" << s - f << " s\n\n";
    printToFile();
    clearResult();

    for (int num = 1; num < n + 1; num++){
        if (n % num == 0) {
            f = clock();
            blocking_mult(num);
            s = clock();
            fout  << "Blocking:\nNum = " << num << " ; " << s - f << " s\n\n";
            printToFile();
            clearResult();
        }
    }
    return 0;
}