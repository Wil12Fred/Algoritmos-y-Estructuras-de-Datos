#include <iostream>
#include <ctime>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

inline void * select(int *A,int n){
  for (int i=0;i<n;i++){
    int men=A[i];
    for (int j=i;j<n;j++){
      if (A[j]<men){
        men=A[j];
        A[j]=A[i];
        A[i]=men;
      }
    }
  }
  return 0;
}

int main(){
  for (int n=10;n<=100000;n*=10){
    int A[n];
    for (int i=0;i<n;i++){
      A[i]=rand()%100;
    }
    auto t0=Time::now();
    select(&A[0],n);
    auto t1=Time::now();
    fsec fs=t1-t0;
    cout << fs.count() << endl;
  }
  return 0;
}
