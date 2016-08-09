template<class T>
struct nodo{
  T m_dato;
  bool color;
  nodo<T>* N[2];
  nodo<T>* padre;
  nodo(){
    color=1;//0->negro 1->rojo
    N[0]=N[1]=0;
    padre=0;
  }
  nodo(T dato,nodo<T>* p){
    m_dato=dato;
    color=1;//0->negro 1->rojo
    N[0]=N[1]=0;
    padre=p;
  }
};
template<class T>
void mergenodo(nodo<T>*a,nodo<T>*b){
  T aux=a->m_dato;
  a->m_dato=b->m_dato;
  b->m_dato=aux;
  bool auxc=a->color;;
  a->color=b->color;
  b->color=auxc;
}

