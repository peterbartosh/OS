#include "pthread.h"
#include "iostream"
#include "fstream"
#include "ctime"
#include "cmath"

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

void* deus_mult(void* args){
    auto* param = (parameters*) args;
    int ii = param->ii,  kk = param->kk,  jj = param->jj,  block = param->block;
    pthread_mutex_t mtx; double sum = 0.;
    for (int i = ii; i < ii + block; i++)
        for (int j = jj; j < jj + block; j++) {
            for (int k = kk; k < kk + block; k++) {
                //cout << sum << "\n";
                sum += M1[i][k] * M2[k][j];
            }
            pthread_mutex_lock(&mtx);
            //cout << ii << " " << jj << " " << kk << " " << block << "\n";
            result[i][j] += sum;
            sum = 0.;
            pthread_mutex_unlock(&mtx);
        }
    return nullptr;
}

void ordinary_mult(){
    auto thr(reinterpret_cast<pthread_t>(deus_mult(new parameters( 0, 0, 0, n))));
    pthread_join(thr, nullptr);
}

void blocking_mult(int num){
    int counter = 0, size = pow(num, 3) + 20;
    auto * threads = new pthread_t[size];
    for (int ii = 0; ii < n; ii += n / num)
        for (int jj = 0; jj < n; jj += n / num)
            for (int kk = 0; kk < n; kk += n / num){
                auto pthread(reinterpret_cast<pthread_t>(deus_mult((void *) new parameters(ii, kk, jj, n / num))));
                threads[counter] = pthread;
                counter++;
            }

    for (int i = 0; i < counter; i++)
        pthread_join(threads[i], nullptr);
}

int main(){
    readFromFile();
    int f, s;
    f = clock_t();
    ordinary_mult();
    s = clock_t();
    fout  << "Ordinary:\n" << s - f << " s\n\n";
    printToFile();
    clearResult();

    for (int num = 1; num < n + 1; num++){
        if (n % num == 0) {
            cout << "DONE " << num << "\n";
            f = clock_t();
            blocking_mult(num);
            s = clock_t();
            fout  << "Blocking:\nNum = " << num << " ; " << s - f << " s\n\n";
            printToFile();
            clearResult();
        }
    }
    return 0;
}