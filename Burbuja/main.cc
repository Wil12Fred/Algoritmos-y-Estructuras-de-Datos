#include <iostream>
#include <chrono>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;
using namespace chrono;

typedef high_resolution_clock Time;
typedef milliseconds ms;
typedef duration<double> fsec;


mutex io_mutex;

int nT = thread::hardware_concurrency();
vector<thread> T;

void F1(int* A,int n,int iT){
  for (int i=0;i<n-1;i++){
    if (i==2 && iT<n){
      T[iT]=thread(F1,A,n,iT+1);
    }
    if (*(A+i)>(*(A+i+1))){
      int aux=*(A+i);
      *(A+i)=*(A+i+1);
      *(A+i+1)=aux;
    }
  }
}

int main(){
  srand(time(0));
  int n;
  cin >> n;
  T.resize(n);
  int A[n];
  for (int i=0;i<n;i++){
    A[i]=rand()%100;
  }
  auto t0 = Time::now();
  T[0] = thread(F1,&A[0], n, 1);
  for (int i=0;i<n;i++){
    if (T[i].joinable())
      T[i].join();
  }
  auto t1=Time::now();
  fsec fs=t1 - t0;
  cout << fs.count() << endl;
  return 0;
}
