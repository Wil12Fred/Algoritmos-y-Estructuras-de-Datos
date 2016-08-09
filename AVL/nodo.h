template<class T>
class nodoAVL{
  public:
    int dato;
    int altura;
    nodoAVL<T>* nodo[2];
    nodoAVL<T>(int n){
      dato = n;
      nodo[0]=nodo[1]= 0;
      altura = 1;
    }
};
template<class T>
int balanceo(nodoAVL<T>* n){
    return altura(n->nodo[1])-altura(n->nodo[0]);
}
template<class T>
inline bool dec(nodoAVL<T>* n ,bool aux){
  return aux?balanceo(n->nodo[aux])<0:balanceo(n->nodo[aux])>0;
}
template<class T>
void actualizar(nodoAVL<T>* n){
  n->altura=max(altura(n->nodo[0]),altura(n->nodo[1]))+1;
}

template<class T>
int altura(nodoAVL<T>* n){
  return n?n->altura:0;
}

template<class T>
nodoAVL<T>* rotar(nodoAVL<T>* n,bool aux){
    nodoAVL<T>* q = n->nodo[aux];
    n->nodo[aux] = q->nodo[!aux];
    q->nodo[!aux] = n;
    actualizar(n);
    actualizar(q);
    return q;
}

template<class T>
nodoAVL<T>* fmin(nodoAVL<T>* n){
    return n->nodo[0]?fmin(n->nodo[0]):n;
}
