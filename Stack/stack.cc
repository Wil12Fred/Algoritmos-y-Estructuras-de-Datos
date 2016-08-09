#include <stdio.h>
template<class T>
class nodo{
  public:
    T dato;
    nodo<T>* next;
    nodo<T>* past;
    nodo(){
      next=past=0;
    }
    nodo(T x){
      dato=x;
      next=past=0;
    }
};
template<class T>
class stack{
  public:
    nodo<T>* top;
    stack(){
      top=0;
    }
    bool empty(){
      if(top==0)
        return 1;
      return 0;
    }
    void push(T x){
      if(!top){
        top=new nodo<T>(x);
        return;
      }
      top->next=new nodo<T>(x);
      top->next->past=top;
      top=top->next;
      return;
    }
    T pop(){
      if(!top)
        printf("Error: underflow\n");
      T r;
      r=top->dato;
      top=top->past;
      return r;
    }
};

int main(){
  return 0;
}
