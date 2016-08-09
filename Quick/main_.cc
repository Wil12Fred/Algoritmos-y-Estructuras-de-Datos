#include <iostream>
#include <vector>
#include <thread>

typedef std::chrono::high_resolution_clock Time;    
typedef std::chrono::milliseconds ms;               
typedef std::chrono::duration<float> fsec;

using namespace std;

void quicksort(int* A,int n,int i,int j,int Ti){//0,n-1
  Ti++;
  int inicio=i;
  int fin =j;
  if (j-i<1) 
    return;
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
  quicksort(A,n,inicio,i-1,Ti*2-1);
  while (A[i]==pib)
    i++;
  if (i<fin)
    quicksort(A,n,i,fin,Ti*2);
  return;
}

int main(){
  srand(time(0));
  for (int n=10;n<=1000000;n*=10){ 
    int A[n];
    for (int i=0;i<n;i++) 
      A[i]=rand()%100;
    auto t1=Time::now();
    quicksort( &A[0],n,0,n-1,0);
    auto t2=Time::now();
    fsec fs=t2-t1;
    cout << fs.count() << endl;
  }
  return 0;
}
