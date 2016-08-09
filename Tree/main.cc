#include <iostream>
#include <stack>
using namespace std;

template <class T>
class nodoT{
  public:
    T m_dato;
    nodoT<T>* nodo[2];
    nodoT(){
      nodo[0]=nodo[1]=NULL;
    }
    nodoT(T dato){
      m_dato=dato;
      nodo[0]=nodo[1]=NULL;
    }
};

template<class T>
void dfs(nodoT<T>* A){//amplitud
  for (int i=0;i<2;i++){
    if (A->nodo[i]){
      dfs(A->nodo[i]);
    }
  }
}

template<class T>
void bfs(nodoT<T>* head){//profundidad
  stack< nodoT<T>* > A ;
  A.push(head);
  while (A.size){
    for (int i=0;i<2;i++){
      if (A.Top()->nodo[i]!=NULL){
        A.push(A.Top()->nodo[i]);
      }
    }
    A.pop();
  }
}

template<class T>
void inOrder(nodoT<T>*A){
  if(A->nodo[0]){
    inOrder(A->nodo[0]);
  }
  cout << A->m_dato << endl;
  if(A->nodo[1]){
    inOrder(A->nodo[1]);
  }
}

template<class T>
struct iteratorTree{
  stack<nodoT<T>*>m_stack;
  nodoT<T>* m_top;
  bool m_estado;
  iteratorTree(nodoT<T>* iterador,bool estado=1){
    m_estado=estado;
    while(iterador){
      m_stack.push(iterador);
      iterador=iterador->nodo[0];
    }
    nodoT<T>* top=m_stack.top();
    m_stack.pop();
    if(top->nodo[1]){
      nodoT<T>* it=top->nodo[1];
      while(it){
        m_stack.push(it);
        it=it->nodo[0];
      }
    }
    m_top=top;
  }
  iteratorTree(){
    m_estado=0;
  }
  void operator ++(int){
    if (m_stack.empty()){
      m_estado=0;
      return;
    }
    nodoT<T>* top=m_stack.top();
    m_stack.pop();
    if(top->nodo[1]){
      nodoT<T>* it=top->nodo[1];
      while(it){
        m_stack.push(it);
        it=it->nodo[0];
      }
    }
    m_top=top;
  }
  bool operator !=(iteratorTree iterador){
    if (!iterador.m_estado && !m_estado){
      return 0;
    }
    return 1;
  }
  T operator *(){
    return m_top->m_dato;
  }
};

template <class T>
class Tree{
  public:
    nodoT<T>* m_head;
    typedef iteratorTree<T> iterator;
    iteratorTree<T> begin(){
      return iteratorTree<T>(m_head);
    }
    iteratorTree<T> end(){
      return iteratorTree<T>();
    }
    Tree(){
      m_head=NULL;
    }
    bool find(T dato,nodoT<T>**& i=0){
      i=&m_head;
      while (*i!=NULL && dato!=(*i)->m_dato){
        i=&((*i)->nodo[(*i)->m_dato < dato]);
      }
      return *i!=NULL;
    }
    void insert(int dato){
      nodoT<T>** t;
      if(!find(dato,t)){
        *t=new nodoT<T>(dato);
      }
    }
};

int main (){
  Tree<int> A;
  for (int i=10;i>0;i--){
    A.insert(i);
  }
  int i=0;
  for (Tree<int>::iterator it=A.begin();it!=A.end();it++){
    cout << *(it) << endl;
  }
  return 0;
}
