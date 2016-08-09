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
  int n;
  static const int nT =thread::hardware_concurrency(); 
  vector<thread> T(nT);
  cin >> n;
  int A[n],aux[n];
  for (int i=0;i<n;i++){
    A[i]=rand()%100;
  }
  auto t0 = Time::now();
  int part=n/6;
  auto t1=Time::now();
  fsec fs=t1-t0;
  cout << fs.count() << endl;
  return 0;
}
