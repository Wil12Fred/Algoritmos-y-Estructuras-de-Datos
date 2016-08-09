#include <iostream>
#include <stdio.h>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>

typedef std::chrono::high_resolution_clock Time;    
typedef std::chrono::milliseconds ms;               
typedef std::chrono::duration<float> fsec; 

using namespace std;

mutex io_mutex;

int nT = thread::hardware_concurrency();
vector<thread> T;

void F1(int* A,int n,int iT){
  for (int i=0;i<n-1;i++){
    if (*(A+i)>(*(A+i+1))){
      int aux=*(A+i);
      *(A+i)=*(A+i+1);
      *(A+i+1)=aux;
    }
  }
}

int main(){
  srand(time(0));
  for (int n=10;n<=1000000;n*=10){
    T.resize(n);
    int A[n];
    for (int i=0;i<n;i++){
      A[i]=rand()%100;
    }
    auto t1=Time::now();
    for (int i=0;i<n;i++){
      F1(&A[0], n, 1);
    }
    auto t2=Time::now();
    fsec fs=t2-t1;
    cout << fs.count() << endl;
  }
  return 0;
}
