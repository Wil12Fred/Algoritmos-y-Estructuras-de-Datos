#include <iostream>
using namespace std;
#include "nodo.h"

template<class T>
void dfs(nodo<T>* i,int nivel=0){
  cout << i->m_dato << " " << nivel << " " << i->color << endl;
  if (i->N[0]){
    dfs(i->N[0],nivel+1);
  }
  if (i->N[1]){
    dfs(i->N[1],nivel+1);
  }
}
template<class T>
void inorden(nodo<T>* i){
  if (i->N[0]){
    inorden(i->N[0]);
  }
  cout << i->m_dato << endl;
  if (i->N[1]){
    inorden(i->N[1]);
  }
}
//color->0=negro color->1=rojo
template <class T>
class tree{
  public:
    nodo<T>* m_head;
    tree(){
      m_head=0;
    }

    nodo<T>* rotar(nodo<T>* n,bool aux){
      nodo<T> **q=&m_head;
      if(n->padre && n->padre->N[1]==n){
        q=&(n->padre->N[1]);
      } else if(n->padre && n->padre->N[0]==n){
        q=&(n->padre->N[0]);
      }
      *q = n->N[!aux];
      (*q)->padre=n->padre;
      n->padre=*q;
      n->N[!aux]=(*q)->N[aux];
      (*q)->N[aux] = n;
      if (n->N[!aux])
        n->N[!aux]->padre=n;
      return *q;
    }

    void coloreo(nodo<T>* n){
      if (n==m_head){//caso 1
        n->color=0;
        return;
      }
      if(n->padre->color==0)//caso 2
        return;
      nodo<T>*p=n->padre;
      nodo<T>*a=p->padre;
      if(a){//caso 3
        nodo<T>* u;
        if (a->N[0]==p){
          u=a->N[1];
        } else if (a->N[1]==p){
          u=a->N[0];
        }
        if (u && u->color==1){
          p->color=u->color=0;
          a->color=1;
          coloreo(a);
          return;
        }
        if((n==p->N[1]) && (p == a->N[0])){//caso 4
          rotar(p,0);
          a=n->padre;
          p=n;
          n=n->N[0];
        } else if ((n==n->padre->N[0]) && (n->padre == a->N[1])){
          rotar(n->padre,1);
          a=n->padre;
          p=n;
          n=n->N[1];
        }
        p->color=0;
        a->color=1;
        if((n==p->N[0]) && (p==a->N[0])){//caso 5
          a=rotar(a,1);
        } else if ((p->N[1]) && (p == a->N[1])){
          a=rotar(a,0);
        }
        if(a->padre==NULL){
          m_head=a;
        }
      }
    }

    bool find(T dato,nodo<T>**&i=0,nodo<T>*&p=0){
      i=&m_head;
      while (*i!=NULL && dato!=(*i)->m_dato){
        p=*i;
        i=&((*i)->N[(*i)->m_dato<dato]);
      }
      return *i!=NULL;
    }

    void insert(T dato){
      nodo<T>** i;
      nodo<T>* p=NULL;
      if(find(dato,i,p))//si se encuentra
        return;
      (*i)=new nodo<T>(dato,p);
      coloreo(*i);
      return;
    }

    inline bool es_hoja(nodo<T>*& n){
      return (n->N[0]==NULL && n->N[1]==NULL);
    }

    void erase(T dato){
      nodo<T>** i;
      nodo<T>* p=NULL;
      if(!find(dato,i,p))//si se encuentra
        return;
      deleting(*i);
      //dfs(*i);
      return;
    }

    nodo<T>* fmax(nodo<T>* n){
      return n->N[1]?fmax(n->N[1]):n;
    }

    nodo<T>* deleting(nodo<T>* z){
      nodo<T>* x,*y;
      if(z->N[0]!=NULL && z->N[1]!=NULL){//si tiene dos hijos
        y=fmax(z->N[0]);//y es el maximo de la izq
      } else{
        y=z;//o es el mismo
      }
      if(y->N[0]!=NULL){//if y tiene hijo izq
        x=y->N[0];//x es el hijo izquierdo de y
      } else {
        x=new nodo<T>(-1,y);//o x es un nodo nulo
      }
      x->padre=y->padre;//padre de x es el mismo que de y
      if(y->padre==NULL){
        if (x->m_dato==-1){
          m_head=NULL;
        } else {
          m_head=x;
        }
      } else{
        if(y==(y->padre)->N[0]){
          if (x->m_dato==-1){
            (y->padre)->N[0]=NULL;
          } else {
            (y->padre)->N[0]=x;
          }
        } else {
          if (x->m_dato==-1){
            (y->padre)->N[1]=NULL;
          } else {
            (y->padre)->N[1]=x;
          }
        }
      }
      if (y!=z){
        z->m_dato=y->m_dato;
      }
      if (y->color==0){
        fix(x);
      }
      return y;
    }

    void fix(nodo<T>* x){
      nodo<T>* w;
      while(x!=m_head && x->color==0){
        if(x==(x->padre)->N[0]){
          fixcolor(x,0);
        } else {
          fixcolor(x,1);
        }
      }
      x->color=0;
    }

    void Rotar(nodo<T>* x,bool aux){//1
      nodo<T>* y=x->N[!aux];//0
      x->N[!aux]=y->N[aux];//1
      y->N[aux]->padre=x;//1
      y->padre=x->padre;
      if(x->padre==NULL){
        m_head=y;
      } else if (x==(x->padre)->N[aux]){
        (x->padre)->N[aux]=y;
      } else {
        (x->padre)->N[!aux]=y;
      }
      y->N[aux]=x;//1
      x->padre=y;
    }

    void fixcolor(nodo<T>* x,bool aux){//0
      nodo<T>* w;
      w=(x->padre)->N[!aux];
      if(w->color==1){
        w->color=0;
        (x->padre)->color=1;
        Rotar(x->padre,0);
        w=(x->padre)->N[!aux];
      }
      if((w->N[aux])->color==0 && (w->N[!aux])==0){
        w->color=1;
        x=x->padre;
      } else {
        if((w->N[!aux])->color==0){
          (w->N[aux])->color=0;
          w->color=1;
          Rotar(w,1);
          w=(x->padre)->N[!aux];
        }
        w->color=(x->padre)->color;
        (x->padre)->color=0;
        (w->N[!aux])->color=0;
        Rotar(x->padre,0);
        x=m_head;
      }
    }
};

int main(){
  tree<int> A;
  for (int i=0;i<10;i++)
    A.insert(i);
  dfs(A.m_head);
  int aux;
  while (cin >> aux){
    cout << "..............." << endl;
    A.erase(aux);
    dfs(A.m_head);
  }
}
