#include <iostream>
#include <thread>
#include <ctime>
#include <vector>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

inline void* F(int *A,int *aux,int i,int j,int k){
  int l;
  int ini=l=i;
  int fin=j-1;
  while (i<=fin && j<=k){
    if (A[i]<A[j]){
      aux[l]=A[i];
      i++;
    } else {
      aux[l]=A[j];
      j++;
    }
    l++;
  }
  if (i==fin+1){
    for (;j<=k;j++){
      aux[l]=A[j];
      l++;
    }
  } else {
    for (;i<=fin;i++){
      aux[l]=A[i];
      l++;
    }
  }
  for (l=ini;l<=k;l++){
    A[l]=aux[l];
  }
  return 0;
}

int main(){
  srand(time(0));
  for (int n=10;n<=1000000;n*=10){
    int A[n],aux[n];
    for (int i=0;i<n;i++){
      A[i]=rand()%100;
    }
    int i=2;
    auto t0 = Time::now();
    for (;i<2*n;i*=2){
      int j=0;
      for (;j<n;j+=i){
        F(&A[0],&aux[0],j,min(n-1,(j+j+i-1)/2+1),min(n-1,j+i-1));
      }
    }
    auto t1=Time::now();
    fsec fs=t1-t0;
    cout << fs.count() << endl;
  }
  return 0;
}
