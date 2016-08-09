#include <stdlib.h>//entrada
#include <ctime>//random
#include <curses.h>//OpenGl salida

using namespace std;

//nodo con dos punteros
template<class T>
class nodo{
  public:
    T m_value;
    nodo<T>* m_left;
    nodo<T>* m_rigth;
    nodo(T value){
      m_value=value;
      m_left=m_rigth=0;
    }
    nodo(){
      m_value=0;
      m_rigth=m_left=0;
    }
};

template<class T>
struct list_iterator{
  nodo<T>* m_puntero;
  list_iterator(nodo<T>* puntero=0){
    m_puntero=puntero;
  }
  list_iterator operator=(list_iterator iterador){
    m_puntero=iterador.m_puntero;
    return *this;
  }
  bool operator!=(list_iterator iterador){
    return m_puntero!=iterador.m_puntero;
  }
  void operator++(int){
    m_puntero=m_puntero->m_left;
  }
  T operator*(){
    return m_puntero->m_value;
  }
};


//lista doblemente enlazada circular
template<class T>
class list{
  public:
    typedef list_iterator<T> iterator;
    nodo<T>* raiz;
    int size;
    //constructores
    list(){
      raiz=new(nodo<T>);
      raiz->m_left=raiz->m_rigth=raiz;
      size=0;
    }
    list(T value){
      raiz=new(nodo<T>)(value);
      raiz->m_left=raiz->m_rigth=raiz;
      size=1;
    }
    //insercion
    void push(T value){
      nodo<T>* aux=new(nodo<T>)(value);
      aux->m_left=raiz->m_left;
      raiz->m_left->m_rigth=aux;
      raiz->m_left=aux;
      aux->m_rigth=raiz;
      size++;
    }
    //eliminar la raiz y desplazarla
    void erase (){
      raiz->m_left->m_rigth=raiz->m_rigth;
      raiz->m_rigth->m_left=raiz->m_left;
      raiz=raiz->m_left;
      size--;
    }
    //mover la raiz
    void move(bool left){
      if (left)
        raiz=raiz->m_rigth;
      else
        raiz=raiz->m_left;
    }
    //interfaz grafica OpenGl GLUT 
    iterator begin(){
      return iterator(raiz);
    }
    iterator end(){
      return iterator(raiz);
    }
    void dibujar(){
      for (iterator it=this->begin();it!=this->end();it++){
        printw("%d ",*it);
      }
      printw("\n");
    }
};

//simulacion
int main(){
  //llenado de vector
  srand(time(0));
  char aux[100];
  initscr();
  (void)echo();
  addstr("Cuantas bombas> ");
  refresh();
  getnstr( aux, sizeof(aux)-1);
  clear();
  int n=atoi(aux);
  bool jugar=true;
  list<int> L(rand()%5+5);
  for (int i=1;i<n;i++)
    L.push(rand()%5+5);
  curs_set(0);
  L.dibujar();
  //controlar tiempo de movimiento en milisegundos
  keypad(stdscr,TRUE);
  timeout(1000);
  while (jugar){
    int ch,mov;
    ch=getch();
    switch(ch){
      case KEY_RIGHT:
        mov=1;
        break;
      case KEY_LEFT:
        mov=0;
        break;
      default:
        mov=-1;
        break;
    }
    //cada segundo verifica el estado del juego
    L.raiz->m_value--;
    //eliminamos el nodo cuando llega a 0
    if (L.raiz->m_value==0){
      L.erase();
      //cuando no hay nodos termina el juego
      if (L.size==0)
        jugar=0;
    }
    //ejecutar movimiento elegido
    if (mov!=-1)
      L.move(mov);
    erase();
    L.dibujar();
    refresh();
  }
  timeout(-1);
  erase();
  printw("Game Over");
  refresh();
  getch();
  endwin();
  return 0;
}
