#include <stdio.h> 
template<class T>
class nodo{
  public:
    T dato;
    nodo<T>* next;
    nodo<T>* past;
    nodo(){
      next=0;
      past=0;
    }
    nodo(T x){
      dato=x;
      next=past=0;
    }
};
template<class T>
class queue{
  public:
    nodo<T>* head;
    nodo<T>* tail;
    queue(){
      head=tail=0;
    }
    bool empty(){
      if(head==0)
        return 1;
      return 0;
    }
    void push(T x){
      if(!tail){
        head=new nodo<T>(x);
        tail=head;
        return;
      }
      tail->next=new nodo<T>(x);
      tail->next->past=tail;
      tail=tail->next;
      return;
    }
    T pop(){
      if(!head){
        printf("Error: underflow\n");
      }
      T r;
      r=head->dato;
      head=head->next;
      return r;
    }
};

int main(){
  return 0;
}
