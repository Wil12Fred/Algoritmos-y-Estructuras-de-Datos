template <class Tr>
class TreeAdtor
{
public:
    Tr* m_Tree;
    TreeAdtor()
    {
        m_Tree = new CBinTree<Traits>;
    }
    template <class T>
    bool insert(T x)
    {
        return m_Tree->Insert(x);
    }
    template <class T>
    bool remove(T x)
    {
        return m_Tree->Remove(x);
    }
    template <class T>
    bool find(T x)
    {
        return m_Tree->Find2(x);
    }
};

template <class T, class C, class E>
class HashTable
{
    public:
    vector<E*> Hash;
    C fun;
    HashTable(T tam)
    {
        Hash.resize(tam, new E);
    }
    bool Insert(T x)
    {
        return Hash[fun(x, Hash.size())]->insert(x);
    }
    bool Find(T x)
    {
        return Hash[fun(x, Hash.size())]->find(x);
    }
    bool Remove(T x)
    {
        return Hash[fun(x, Hash.size())]->remove(x);
    }
};
