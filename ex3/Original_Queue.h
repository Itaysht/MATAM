#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>

template <class T>
class Original_Queue
{
    template <class S>
    class Node
    {
        S* m_firstNode;
        Node<S>* m_nextNode;

    public:
        Node() {m_firstNode = new S(); m_nextNode = nullptr;};
        Node(const S& first) {m_firstNode = new S(first); m_nextNode = nullptr;};
        Node(const Node& node) {m_firstNode = new S(node.m_firstNode); m_nextNode = node.m_nextNode;};
        ~Node() {delete m_firstNode;};
        Node& operator=(const Node& node)
        {
            if (this == &node)
            {
                return *this;
            }
            S* temp = m_firstNode;
            Node<S>* tempNext = m_nextNode;
            m_firstNode = node.m_firstNode;
            m_nextNode = node.m_nextNode;
            delete temp;
            delete tempNext;
            return *this;
        };
        S& getS() {return *m_firstNode;};

        void setNext(Node<S>* node)
        {
            m_nextNode = node;
        };

        Node<T>* next() {return m_nextNode;};

        void add(const S& next)
        {
            Node<S>* temp = new Node<S>(next);
            m_nextNode = temp;
        };
    };
    int m_size;
    Node<T>* m_PointerToFirstNode;
    Node<T>* m_PointerToLastNode;

public:
    Original_Queue();
    Original_Queue(const Original_Queue& queue);
    ~Original_Queue();
    Original_Queue& operator=(const Original_Queue& queue);

    void pushBack(const T& val);
    T& front() const;
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin();
    Iterator end();

    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};

};
//------------------------Iterator class--------------------//
template <class T>
class Original_Queue<T>::Iterator
{
    const Original_Queue<T>* m_queue;
    int index;
    Iterator(const Original_Queue<T>* queue, int otherIndex);
    friend class Original_Queue<T>;
public:
    T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};
};

template <class T>
typename Original_Queue<T>::Iterator Original_Queue<T>::begin()
{
    return Iterator(this, 0);
}

template <class T>
typename Original_Queue<T>::Iterator Original_Queue<T>::end()
{
    return Iterator(this, m_size);
}

template <class T>
Original_Queue<T>::Iterator::Iterator(const Original_Queue<T>* queue, int otherIndex) : m_queue(queue), index(otherIndex) {}

template <class T>
T &Original_Queue<T>::Iterator::operator*() const
{
    if (index == m_queue->m_size)
    {
        throw Original_Queue<T>::Iterator::InvalidOperation();
    }
    Node<T>* temp = m_queue->m_PointerToFirstNode;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next();
    }
    return temp->getS();
}

template <class T>
typename Original_Queue<T>::Iterator& Original_Queue<T>::Iterator::operator++()
{
    if (index == m_queue->m_size)
    {
        throw Original_Queue<T>::Iterator::InvalidOperation();
    }
    index++;
    return *this;
}

template <class T>
bool Original_Queue<T>::Iterator::operator!=(const Iterator &it) const
{
    return index != it.index;
}
//----------------------End of Iterator class---------------------//

//----------------------Const Iterator class----------------------//
template <class T>
class Original_Queue<T>::ConstIterator
{
    const Original_Queue<T>* m_queue;
    int index;
    ConstIterator(const Original_Queue<T>* queue, int otherIndex);
    friend class Original_Queue<T>;
public:
    const T& operator*() const;
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& it) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation{};
};

template <class T>
typename Original_Queue<T>::ConstIterator Original_Queue<T>::begin() const
{
    return ConstIterator(this, 0);
}

template <class T>
typename Original_Queue<T>::ConstIterator Original_Queue<T>::end() const
{
    return ConstIterator(this, m_size);
}

template <class T>
Original_Queue<T>::ConstIterator::ConstIterator(const Original_Queue<T>* queue, int otherIndex) : m_queue(queue), index(otherIndex) {}

template <class T>
const T &Original_Queue<T>::ConstIterator::operator*() const
{
    if (index == m_queue->m_size)
    {
        throw Original_Queue<T>::ConstIterator::InvalidOperation();
    }
    Node<T>* temp = m_queue->m_PointerToFirstNode;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next();
    }
    return temp->getS();
}

template <class T>
typename Original_Queue<T>::ConstIterator& Original_Queue<T>::ConstIterator::operator++()
{
    if (index == m_queue->m_size)
    {
        throw Original_Queue<T>::ConstIterator::InvalidOperation();
    }
    index++;
    return *this;
}


template <class T>
bool Original_Queue<T>::ConstIterator::operator!=(const ConstIterator &it) const
{
    return index != it.index;
}
//---------------------End of ConstIterator----------------------//

//----------------------Implementation of Original_Queue------------------//
template <class T>
Original_Queue<T>::Original_Queue() :  m_size(0), m_PointerToFirstNode(nullptr),
                     m_PointerToLastNode(nullptr) {}

template <class T>
Original_Queue<T>::Original_Queue(const Original_Queue<T>& queue)
{
    m_PointerToFirstNode = new Node<T>(queue.m_PointerToFirstNode->getS());
    Node<T>* runsOnThis = m_PointerToFirstNode;
    Node<T>* runsOnQueue;
    Node<T>* temp;
    runsOnQueue = queue.m_PointerToFirstNode->next();
    while (runsOnQueue != nullptr)
    {
        try
        {
            temp = new Node<T>(runsOnQueue->getS());
        }
        catch (const std::bad_alloc&)
        {
            Node<T>* tempDelete = m_PointerToFirstNode;
            Node<T>* tempNext;
            while (tempDelete != nullptr)
            {
                tempNext = tempDelete->next();
                delete tempDelete;
                tempDelete = tempNext;
            }
            throw;
        }
        runsOnThis->setNext(temp);
        runsOnThis = runsOnThis->next();
        runsOnQueue = runsOnQueue->next();
    }
    m_PointerToLastNode = runsOnThis;
    m_size = queue.m_size;
}

template <class T>
Original_Queue<T> &Original_Queue<T>::operator=(const Original_Queue<T> &queue)
{
    if (this == &queue)
    {
        return *this;
    }
    Node<T>* tempDel = m_PointerToFirstNode;
    Node<T>* temp = tempDel;
    m_PointerToFirstNode = new Node<T>(queue.m_PointerToFirstNode->getS());
    Node<T> *runsOnThis = m_PointerToFirstNode;
    Node<T> *runsOnQueue;
    try
    {
        runsOnQueue = queue.m_PointerToFirstNode->next();
        while (runsOnQueue != nullptr)
        {
            temp = new Node<T>(runsOnQueue->getS());
            runsOnThis->setNext(temp);
            runsOnThis = runsOnThis->next();
            runsOnQueue = runsOnQueue->next();
        }
        m_PointerToLastNode = runsOnThis;
        temp = tempDel;
        while (tempDel != nullptr) {
            temp = tempDel->next();
            delete tempDel;
            tempDel = temp;
        }
    }
    catch (const std::bad_alloc&)
    {
        runsOnThis = m_PointerToFirstNode;
        while (runsOnThis != nullptr)
        {
            temp = runsOnThis->next();
            delete runsOnThis;
            runsOnThis = temp;
        }
        m_PointerToFirstNode = tempDel;
        throw;
    }
    m_size = queue.m_size;
    return *this;
}

template <class T>
Original_Queue<T>::~Original_Queue()
{
    Node<T>* temp = m_PointerToFirstNode;
    Node<T>* tempNext = temp;
    while (temp != nullptr)
    {
        tempNext = temp->next();
        delete temp;
        temp = tempNext;
    }
    m_PointerToFirstNode = nullptr;
    m_PointerToLastNode = nullptr;
}

template <class T>
void Original_Queue<T>::pushBack(const T& val)
{
    if (m_PointerToLastNode == nullptr)
    {
        Node<T> *temp = new Node<T>(val);
        m_PointerToFirstNode = temp;
        m_PointerToLastNode = temp;
    }
    else
    {
        m_PointerToLastNode->add(val);
        m_PointerToLastNode = m_PointerToLastNode->next();
    }
    m_size++;
}

template <class T>
T& Original_Queue<T>::front() const
{
    if (m_size == 0)
    {
        throw Original_Queue<T>::EmptyQueue();
    }
    return m_PointerToFirstNode->getS();
}

template <class T>
void Original_Queue<T>::popFront()
{
    if (m_size == 0)
    {
        throw Original_Queue<T>::EmptyQueue();
    }
    if (m_size == 1)
    {
        delete m_PointerToFirstNode;
        m_PointerToFirstNode = nullptr;
        m_PointerToLastNode = nullptr;
    }
    else
    {
        Node<T> *temp = m_PointerToFirstNode;
        m_PointerToFirstNode = m_PointerToFirstNode->next();
        delete temp;
    }
    m_size--;
}

template <class T>
int Original_Queue<T>::size() const
{
    return m_size;
}

template <class T, class Condition>
Original_Queue<T> filter(const Original_Queue<T>& queue, Condition c)
{
    Original_Queue<T> temp;
    for (const T& org : queue)
    {
        if (c(org))
        {
            temp.pushBack(org);
        }
    }
    return temp;
}

template <class T, class Changing>
void transform(Original_Queue<T>& queue, Changing c)
{
    for (T& org : queue)
    {
        c(org);
    }
}

#endif // MY_QUEUE_H