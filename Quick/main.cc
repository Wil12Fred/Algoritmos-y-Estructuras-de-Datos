#include <iostream>
#include <chrono>
#include <vector>
#include <thread>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

using namespace std;

vector<thread>T;

inline void* quicksort(int* A,int n,int i,int j,int Ti){
  Ti++;
  int inicio=i;
  int fin =j;
  if (j-i<1) return 0;
  int pib=A[i];
  while (j-i>0){
    while (i<=fin && A[i]<pib)
      i++;
    while (j>=inicio && A[j]>=pib)
      j--;
    if (j-i>0){
      int aux=A[j];
      A[j]=A[i];
      A[i]=aux;
      i++;
      j--;
    }
  }
  while (i<=fin && A[i]<pib)
    i++;
  while (j>=inicio && A[j]>=pib)
    j--;
  T[Ti*2-1]=thread(quicksort,A,n,inicio,i-1,Ti*2-1);
  while (A[i]==pib) i++;
  if (i<fin){
    T[Ti*2]=thread(quicksort,A,n,i,fin,Ti*2);
  }
  T[Ti*2-1].join();
  if (i<fin){
    T[Ti*2].join();
  }
  return 0;
}

int main(){
  srand(time(0));
  int n;
  cin >> n;
  T.resize(n*n);
  int A[n];
  for (int i=0;i<n;i++) 
    A[i]=rand()%100;
  auto t0=Time::now();
  T[0]=thread(quicksort, &A[0],n,0,n-1,0);
  T[0].join();
  auto t1=Time::now();
  fsec fs=t1-t0;
  cout << fs.count() << endl;
  return 0;
}
