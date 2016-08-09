#include <iostream>
#include <chrono>
#include <ctime>

typedef std::chrono::high_resolution_clock Time;  
typedef std::chrono::milliseconds ms;             
typedef std::chrono::duration<float> fsec;

using namespace std;

inline void* insert(int *A,int n){
  int pos,i;
  i=pos=1;
  while (i<n){
    while (i<n && A[i-1]<=A[i])
      i++;
    pos=i;
    if (i<n){
      while (i>0 && A[i-1]>A[i]){
        swap(A[i-1],A[i]);
        i--;
      }
    }
    i=pos+1;
  }
  return 0;
}

int main(){
  srand(time(0));
  for (int n=10;n<=1000000;n*=10){
    int A[n];
    for (int i=0;i<n;i++)
      A[i]=rand()%100;
    auto t1=Time::now();
    insert (&A[0],n);
    auto t2=Time::now();
    fsec fs= t2-t1;
    cout << fs.count() << endl;
  }
  return 0;
}
