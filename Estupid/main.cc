#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>
#include <stdio.h>

typedef std::chrono::high_resolution_clock Time;    
typedef std::chrono::milliseconds ms;               
typedef std::chrono::duration<float> fsec;

using namespace std;

mutex io_mutex;

int nT=thread::hardware_concurrency();
vector<thread> T;

bool ord(int* A,int n){
  for (int i=0;i<n-1;i++)
    if (*(A+i+1)<*(A+i)) return 0;
  return true;
}

void F(int* A,int i,int n){
  *(A+i)=rand()%n;
  return;
}

int main (){
  srand(time(0));
  int n;
  cin >> n;
  T.resize(n);
  int A[n];
  for (int i=0;i<n;i++){
    A[i]=rand()%100;
  }
  int S[n];
  auto t0=Time::now();
  while (ord(&A[0],n)==0){
    for (int i=0;i<n;i++){
      T[i]=thread(F,&S[0],i,n);
    }
    for (int i=0;i<n;i++){
      T[i].join();
      int swap=S[i];
      int aux=A[i];
      A[i]=A[swap];
      A[swap]=aux;
    }
  }
  auto t1=Time::now();
  fsec fs=t1-t0;
  cout << fs.count() << endl;
  return 0;
}
