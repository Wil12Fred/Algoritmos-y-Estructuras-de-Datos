#include <iostream>
#include <vector>
#define Prime 53

using namespace std;

template<class T>
struct functionHash{
  inline T operator()(T a,T b){
    return a*Prime+b;
  }
};

template<class T,class C>
class hTable:public vector<T> {
  public:
    C fun;
    hTable(T tam){
      this->resize(tam);
    }
    bool insert(T x){
    }
    bool find(T x){
    }
    bool remove(T x){
    }
};

int main(){
  int n;
  cin >> n;
  hTable<int,functionHash<int> > A(n);
  return 0;
}
