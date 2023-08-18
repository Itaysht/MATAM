#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

const int INITIAL_SIZE = 1;

//===============INTERFACE===============//
template <class T>
class Other2_Queue
{
public:
    Other2_Queue(int size = 0); //C'tor of Other2_Queue
    Other2_Queue(const Other2_Queue& queue); // Copy c'tor of Other2_Queue
    ~Other2_Queue(); //D'tor of Other2_Queue
    Other2_Queue& operator=(const Other2_Queue& queue); //Assignment operator of Other2_Queue

    /*
     * Adds a new node to the end of the queue.
     *
     * @param node - the node that is added.
     * @return
     *      void
     */
    void pushBack(const T& node);

    /*
     * Returns the first node in the queue.
     *
     * @return
     *      The first node in the queue
     */
    T& front();

    /*
     * Releases the first node in the queue.
     *
     * @return
     *      void
     */

    T& front() const;

    void popFront();

    /*
     * Returns the size of the queue.
     *
     * @return
     *      The size of the queue
     */
    const int size() const;

    /*
     * Iterator of queue.
     */
    class Iterator;
    class ConstIterator;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

    class EmptyQueue //exceptions
    {
        EmptyQueue() = default;
    };

private:
    T* m_data; //The array that contains the data of the queue
    int m_size; //The size of the queue
    int m_max_size; //The max size of the curret queue
    int m_front; //The index of the first node in the queue

    const int getFront() const; //returns the index of the first node
    const int getEnd() const; //returns the amount of nodes in data array
    const int getMaxSize() const; //return the max size
    T& getData(int index); //returns a reference to a node

};

/*
    * Filters a queue using a specific condition.
    *
    * @param queue - The queue to be filtered.
    * @param c - The condition to filter the queue with.
    * @return
    *      The filtered queue
    */
template<class T, class Condition>
Other2_Queue<T> filter(Other2_Queue<T> queue, Condition c);

/*
* Changed the nodes in the queue using a specific condition.
*
* @param queue - The queue to be filtered.
* @param c - The condition to change the nodes with.
* @return
*      void
*/
template<class T, class Condition>
void transform(Other2_Queue<T>& queue, Condition c);

//===============INTERFACE===============//

//=============IMPLEMENTATION=============//
template <class T>
Other2_Queue<T>::Other2_Queue(int size) : m_data(new T[size >= INITIAL_SIZE ? size : INITIAL_SIZE]),
                            m_size(0),
                            m_max_size(size >= INITIAL_SIZE ? size : INITIAL_SIZE),
                            m_front(0) {}

template <class T>
Other2_Queue<T>::Other2_Queue(const Other2_Queue<T>& queue) : m_data(new T[queue.size()]),
                                         m_size(queue.size()), m_max_size(queue.size()),
                                         m_front(queue.getFront())
{
    for (int i = queue.getFront(); i < queue.getEnd(); i++)
    {
        m_data[i - queue.getFront()] = queue.m_data[i];
    }
}

template <class T>
Other2_Queue<T>::~Other2_Queue()
{
    delete[] m_data;
}

template <class T>
Other2_Queue<T>& Other2_Queue<T>:: operator=(const Other2_Queue<T>& queue) {
    if (this == &queue)
    {
        return *this;
    }

    delete[] m_data;
    m_data = new T[queue.size()];
    m_size = queue.size();
    m_max_size = queue.size();
    m_front = queue.getFront();

    for (int i = queue.getFront(); i < queue.getEnd(); i++)
    {
        m_data[i - queue.getFront()] = queue.m_data[i];
    }
    return *this;
}

template <class T>
void Other2_Queue<T>::pushBack(const T& node)
{
    if (this->getEnd() == this->getMaxSize())
    {
        T* temp = (new T[(this->size())*2]);
        for (int i = this->getFront(); i < this->getEnd(); i++)
        {
            temp[i - this->getFront()] = m_data[i];
        }
        delete[] m_data;
        m_max_size = (this->size())*2;
        m_size -= m_front;
        m_data = temp;
        m_front = 0;
    }
    m_data[(this->size()) + this->getFront()] = node;
    m_size++;
}

template <class T>
T& Other2_Queue<T>::front()
{
    if (this->size() == 0)
    {
        throw Other2_Queue<T>::EmptyQueue();
    }
    return m_data[this->getFront()];
}

template <class T>
T& Other2_Queue<T>::front() const
{
    if (this->size() == 0)
    {
        throw Other2_Queue<T>::EmptyQueue();
    }
    return m_data[this->getFront()];
}

template <class T>
void Other2_Queue<T>::popFront()
{
    if (this->size() == 0)
    {
        throw Other2_Queue<T>::EmptyQueue();
    }
    m_front++;
}
template <class T>
const int Other2_Queue<T>::size() const
{
    return m_size - m_front;
}

template <class T>
const int Other2_Queue<T>::getFront() const
{
    return m_front;
}

template <class T>
const int Other2_Queue<T>::getEnd() const
{
    return m_size;
}

template <class T>
const int Other2_Queue<T>::getMaxSize() const
{
    return m_max_size;
}

template <class T>
T& Other2_Queue<T>::getData(int index)
{
    return m_data[index];
}

//===============ITERATOR===============//

template <class T>
class Other2_Queue<T>::Iterator
{
    Other2_Queue<T>* m_queue;
    int m_index;
    Iterator(Other2_Queue<T>* queue, int index);
    friend class Other2_Queue<T>;

public:
    T& operator*() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& it) const;
    bool operator!=(const Iterator& it) const;
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;

    class InvalidOperation //exceptions
    {
        InvalidOperation() = default;
    };
};

template<class T>
Other2_Queue<T>::Iterator::Iterator(Other2_Queue<T>* queue, int index) :
        m_queue(queue), m_index(index){}

template<class T>
T& Other2_Queue<T>::Iterator::operator*() const
{
    if (m_index >= m_queue->getEnd())
    {
        throw Other2_Queue<T>::Iterator::InvalidOperation();
    }
    return m_queue->m_data[m_index];
}

template<class T>
typename Other2_Queue<T>::Iterator& Other2_Queue<T>::Iterator::operator++()
{
    if (m_index >= m_queue->getEnd())
    {
        throw Other2_Queue<T>::Iterator::InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
typename Other2_Queue<T>::Iterator Other2_Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Other2_Queue<T>::Iterator::operator==(const Iterator& it) const
{
    return m_index == it.m_index;
}

template<class T>
bool Other2_Queue<T>::Iterator::operator!=(const Iterator& it) const
{
    return !(*this == it);
}

template <class T>
typename Other2_Queue<T>::Iterator Other2_Queue<T>::begin()
{
    return Iterator(this, this->getFront());
}

template <class T>
typename Other2_Queue<T>::Iterator Other2_Queue<T>::end()
{
    return Iterator(this, this->getEnd());
}

//===============ITERATOR===============//

//===============CONST_ITERATOR===============//

template <class T>
class Other2_Queue<T>::ConstIterator
{
    const Other2_Queue<T>* m_queue;
    int m_index;
    ConstIterator(const Other2_Queue<T>* queue, int index);
    friend class Other2_Queue<T>;

public:
    const T& operator*() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator==(const ConstIterator& it) const;
    bool operator!=(const ConstIterator& it) const;
    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;

    class InvalidOperation //exceptions
    {
        InvalidOperation() = default;
    };
};

template<class T>
Other2_Queue<T>::ConstIterator::ConstIterator(const Other2_Queue<T>* queue, int index) :
        m_queue(queue), m_index(index){}

template<class T>
const T& Other2_Queue<T>::ConstIterator::operator*() const
{
    if (m_index >= m_queue->getEnd())
    {
        throw Other2_Queue<T>::ConstIterator::InvalidOperation();
    }
    return m_queue->m_data[m_index];
}

template<class T>
typename Other2_Queue<T>::ConstIterator& Other2_Queue<T>::ConstIterator::operator++()
{
    if (m_index >= m_queue->getEnd())
    {
        throw Other2_Queue<T>::ConstIterator::InvalidOperation();
    }
    ++m_index;
    return *this;
}

template<class T>
typename Other2_Queue<T>::ConstIterator Other2_Queue<T>::ConstIterator::operator++(int)
{
    ConstIterator result = *this;
    ++*this;
    return result;
}

template<class T>
bool Other2_Queue<T>::ConstIterator::operator==(const ConstIterator& it) const
{
    return m_index == it.m_index;
}

template<class T>
bool Other2_Queue<T>::ConstIterator::operator!=(const ConstIterator& it) const
{
    return !(*this == it);
}

template <class T>
typename Other2_Queue<T>::ConstIterator Other2_Queue<T>::begin() const
{
    return ConstIterator(this, this->getFront());
}

template <class T>
typename Other2_Queue<T>::ConstIterator Other2_Queue<T>::end() const
{
    return ConstIterator(this, this->getEnd());
}

//===============CONST_ITERATOR===============//
template<class T, class Condition>
Other2_Queue<T> filter(Other2_Queue<T> queue, Condition c)
{
    Other2_Queue<T> temp = queue;
    Other2_Queue<T> result = Other2_Queue<T>(queue.size());
    for (int i = 0; i < queue.size(); i++)
    {
        if (c(temp.front()))
        {
            result.pushBack(temp.front());
        }
        temp.popFront();
    }
    return result;
}

template<class T, class Condition>
void transform(Other2_Queue<T>& queue, Condition c)
{
    Other2_Queue<T> temp = queue;
    int sizeOfQueue = queue.size();
    for (int i = 0; i < sizeOfQueue; i++)
    {
        queue.popFront();
    }
    for (int i = 0; i < sizeOfQueue; i++)
    {
        c(temp.front());
        queue.pushBack(temp.front());
        temp.popFront();
    }

}
//=============IMPLEMENTATION=============//

#endif /* QUEUE_H */
