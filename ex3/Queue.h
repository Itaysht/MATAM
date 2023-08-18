#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>

//------------------------Interface--------------------//
template <class T>
class Queue
{
    public:
    Queue(); //C'tor of Queue
    Queue(const Queue& queue); // Copy c'tor of Queue
    ~Queue(); //D'tor of Queue
    Queue& operator=(const Queue& queue); //Assignment operator of Queue

    /*
     * Adds a new node to the end of the queue.
     *
     * @param val - the node that is added.
     * @return 
     *      void
     */
    void pushBack(const T& val);

    /*
     * Returns the first node in the queue.
     *
     * @return 
     *      The first node in the queue
     */
    T& front() const;

    /*
     * Releases the first node in the queue.
     *
     * @return 
     *      void
     */
    void popFront();

    /*
     * Returns the size of the queue.
     *
     * @return 
     *      The size of the queue
     */
    int size() const;

    /*
     * Iterator of queue.
     */
    class Iterator;
    Iterator begin();
    Iterator end();

    /*
     * Const Iterator of queue.
     */
    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue{};

    private:
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
    int m_size; //size of queue
    Node<T>* m_PointerToFirstNode; //pointer to first node of queue
    Node<T>* m_PointerToLastNode; //pointer to last node of queue

};

/*
* Filters a queue using a specific condition.
*
* @param queue - The queue to be filtered.
* @param c - The condition to filter the queue with.  
* @return 
*      The filtered queue
*/
template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition c);

/*
* Changed the nodes in the queue using a specific condition.
*
* @param queue - The queue to be filtered.
* @param c - The condition to change the nodes with.  
* @return 
*      void
*/
template <class T, class Changing>
void transform(Queue<T>& queue, Changing c);
//------------------------End of Interface--------------------//

//------------------------Iterator class--------------------//
template <class T>
class Queue<T>::Iterator
{
    const Queue<T>* m_queue;
    int index;
    Iterator(const Queue<T>* queue, int otherIndex);
    friend class Queue<T>;
public:
    T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation{};
};

template <class T>
typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, 0);
}

template <class T>
typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, m_size);
}

template <class T>
Queue<T>::Iterator::Iterator(const Queue<T>* queue, int otherIndex) : m_queue(queue), index(otherIndex) {}

template <class T>
T &Queue<T>::Iterator::operator*() const
{
    if (index == m_queue->m_size)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    Node<T>* temp = m_queue->m_PointerToFirstNode;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next();
    }
    return temp->getS();
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (index == m_queue->m_size)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    index++;
    return *this;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator &it) const
{
    return index != it.index;
}
//----------------------End of Iterator class---------------------//

//----------------------Const Iterator class----------------------//
template <class T>
class Queue<T>::ConstIterator
{
    const Queue<T>* m_queue;
    int index;
    ConstIterator(const Queue<T>* queue, int otherIndex);
    friend class Queue<T>;
public:
    const T& operator*() const;
    ConstIterator& operator++();
    bool operator!=(const ConstIterator& it) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation{};
};

template <class T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, 0);
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, m_size);
}

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int otherIndex) : m_queue(queue), index(otherIndex) {}

template <class T>
const T &Queue<T>::ConstIterator::operator*() const
{
    if (index == m_queue->m_size)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    Node<T>* temp = m_queue->m_PointerToFirstNode;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next();
    }
    return temp->getS();
}

template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (index == m_queue->m_size)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    index++;
    return *this;
}


template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator &it) const
{
    return index != it.index;
}
//---------------------End of ConstIterator----------------------//

//----------------------Implementation of Queue------------------//
template <class T>
Queue<T>::Queue() :  m_size(0), m_PointerToFirstNode(nullptr),
                     m_PointerToLastNode(nullptr) {}

template <class T>
Queue<T>::Queue(const Queue<T>& queue)
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
Queue<T> &Queue<T>::operator=(const Queue<T> &queue)
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
Queue<T>::~Queue()
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
void Queue<T>::pushBack(const T& val)
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
T& Queue<T>::front() const
{
    if (m_size == 0)
    {
        throw Queue<T>::EmptyQueue();
    }
    return m_PointerToFirstNode->getS();
}

template <class T>
void Queue<T>::popFront()
{
    if (m_size == 0)
    {
        throw Queue<T>::EmptyQueue();
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
int Queue<T>::size() const
{
    return m_size;
}

template <class T, class Condition>
Queue<T> filter(const Queue<T>& queue, Condition c)
{
    Queue<T> temp;
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
void transform(Queue<T>& queue, Changing c)
{
    for (T& org : queue)
    {
        c(org);
    }
}
//----------------------End of Implementation of Queue------------------//

#endif // MY_QUEUE_H