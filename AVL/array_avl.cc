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
    T suma_acumulada;
    AVL(){
      suma_acumulada=0;
      m_head=NULL;
    }
    void insert(int dato){
      suma_acumulada+=dato;
      m_head=inserting(m_head,dato);
    }
    void remove(int dato){
      suma_acumulada-=dato;
      m_head=removing(m_head,dato);
    }
    int sum(){
      return suma_acumulada;
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

void quicksort(AVL<int>** A,int n,int i,int j,int Ti){//0,n-1
  Ti++;
  int inicio=i;
  int fin =j;
  if (j-i<1) 
    return;
  int pib=A[i]->sum();
  while (j-i>0){
    while (i<=fin && A[i]->sum()<pib)
      i++;
    while (j>=inicio && A[j]->sum()>=pib)
      j--;
    if (j-i>0){
      AVL<int>* aux=A[j];
      A[j]=A[i];
      A[i]=aux;
      i++;
      j--;
    }
  }
  while (i<=fin && A[i]->sum()<pib)
    i++;
  while (j>=inicio && A[j]->sum()>=pib)
    j--;
  quicksort(A,n,inicio,i-1,Ti*2-1);
  while (A[i]->sum()==pib)
    i++;
  if (i<fin)
    quicksort(A,n,i,fin,Ti*2);
  return;
}

int main (){
  int n;
  cout << "tamanio del array: ";
  cin >> n;
  AVL<int>* A[n];
  while (1){
    int decision;
    cout << "insert(1)-remove(2)-quicksort(3)" << endl;
    cin >> decision;
    if (decision==1){
      cout << "cuantos elementos desea insertar: ";
      cin >> n;
      for (int i=0;i<n;i++){
        int pos,a;
        cout << "posicion: ";
        cin >> pos;
        cout << "dato: ";
        cin >> a;
        A[pos]->insert(a);
      }
    }
    if (decision==2){
      int pos,a;
      cout << "posicion: ";
      cin >> pos;
      cout << "dato: ";
      cin >> a;
      A[pos]->remove(a);
    }
    if (decision==3){
      quicksort(A,n,0,n-1,0);
    }
  }
  return 0;
}
