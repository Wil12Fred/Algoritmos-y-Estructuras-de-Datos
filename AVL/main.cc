#include <iostream>
using namespace std;
#include "nodo.h"

template<class T>
nodoAVL<T>* rmin(nodoAVL<T>* n){                       
  if( n->nodo[0]==0 )                          
    return n->nodo[1];                       
  n->nodo[0] = rmin(n->nodo[0]);               
  return balancear(n);                           
}

template<class T>
nodoAVL<T>* balancear(nodoAVL<T>* n){
    actualizar(n);
    if(abs(balanceo(n))!=2)
      return n;
    bool aux=(balanceo(n)==2);
    if (dec(n,aux)){
      n->nodo[aux]=rotar(n->nodo[aux],!aux);
    }
    return rotar(n,aux);
}

template<class T>
nodoAVL<T>* inserting(nodoAVL<T>* n, int dato){
    if( !n )
      return new nodoAVL<T>(dato);
    bool aux=!(dato<n->dato);
    n->nodo[aux] = inserting(n->nodo[aux],dato);
    return balancear(n);
}

template<class T>
nodoAVL<T>* removing(nodoAVL<T>* n, int dato){
    if( !n ) 
      return 0;
    if(n->dato==dato){
      nodoAVL<T>* pp=n;//duplico
      delete n;
      if( !pp->nodo[1] ) return pp->nodo[0];
      nodoAVL<T>* aux = fmin(pp->nodo[1]);//aux
      aux->nodo[1] = rmin(pp->nodo[1]);
      aux->nodo[0] = pp->nodo[0];
      return balancear(aux);
    }
    bool aux=!(dato<n->dato);
    n->nodo[aux] = removing(n->nodo[aux],dato);
    return balancear(n);
}
template<class T>
class AVL{
  public:
    nodoAVL<T>* m_head;
    AVL(){
      m_head=NULL;
    }
    void insert(int dato){
      m_head=inserting(m_head,dato);
    }
    void remove(int dato){
      m_head=removing(m_head,dato);
    }
};


template<class T>
void dfs(nodoAVL<T>* n,int nivel=0){
  if(n){
    cout << n->dato << " "  << nivel<<  endl;
    dfs(n->nodo[0],nivel+1);
    dfs(n->nodo[1],nivel+1);
  }
}

int main (){
  AVL<int> A;
  while (1){
    int decision;
    cout << "insert-remove" << endl;
    cin >> decision;
    if (decision==1){
      int n;
      cin >> n;
      for (int i=0;i<n;i++){
        int a;
        cin >> a;
        A.insert(a);
      }
      dfs(A.m_head);
    }
    if (decision==2){
      int aux;
      cin >> aux;
      A.remove(aux);
      dfs(A.m_head);
    }
  }
  return 0;
}
