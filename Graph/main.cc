#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<class G>
class CNode{
  typedef typename G::N N;
  typedef typename G::Edge Edge;
  public:
    N m_data;
    list<Edge*> m_edges;
    CNode(N x){
      m_data=x;
    }
};

template<class G>
class CEdge{
  typedef typename G::Node Node;
  typedef typename G::E E;
  public:
    E m_data;
    Node* m_nodes[2];
    bool m_dir;
    CEdge(Node* a,Node* b,E x,bool dir){
      m_data=x;
      m_nodes[0]=a;
      m_nodes[1]=b;
      m_dir=dir;
    }
};

template <class Nd,class Ed>
class CGraph{
  public:
    typedef CGraph<Nd,Ed> Self;
    typedef CNode<Self> Node;
    typedef CEdge<Self> Edge;
    typedef Nd N;
    typedef Ed E;
    vector<Node*> m_nodes;
    void insertNode(N x){
      m_nodes.push_back(new Node(x));
    }
    void insertEdge(Node *a,Node *b,Ed x,bool dir){
      (a->m_edges).push_back(new Edge(a,b,x,dir));
      (b->m_edges).push_back(new Edge(a,b,x,dir));
    }
};

int main(){
  CGraph<int,int> G;
  G.insertNode(3);
}
