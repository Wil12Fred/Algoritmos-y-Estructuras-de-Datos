#include <iostream>
#include <ctime>

typedef std::chrono::high_resolution_clock Time;  
typedef std::chrono::milliseconds ms;             
typedef std::chrono::duration<float> fsec;        

using namespace std;

void busq( int *A, int i, int j){
    int ini = i;
    while ( ini*2+1 < j ) {
      int v = 2*ini + 1;
      if ((v + 1 < j) && A[v]<A[v+1]) {
          v++;
      }
      if (A[ini]<A[v]) {
        int t=A[v];
        A[v]=A[ini];
        A[ini]=t;
        ini = v;
      } else {
          return;
      }
    }
}

void heap( int *A, int count){
    int i, j;
 
    for (i = (count-2)/2; i >=0; i--) {
        busq( A, i, count);
    }
 
    for (j=count-1; j > 0; j--) {
      int t=A[j];
      A[j]=A[0];
      A[0]=t;
      busq(A, 0, j);
    }
}

int main(){
  srand(time(0));
  for (int n=10;n<=1000000;n*=10){
    int A[n];
    for (int i=0;i<n;i++)
      A[i]=rand()%100;
    auto t1=Time::now();
    heap(&A[0], n);
    auto t2=Time::now();
    fsec fs=t2-t1;
    cout << fs.count() << endl;
  }
  return 0;
}
