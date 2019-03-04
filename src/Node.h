#ifndef NIBBELS_LISTNODE_H
#define NIBBELS_LISTNODE_H

template<typename T>
struct Node{
    //element typu T
    T item;

    //wskaźnik na następny element typu T
    Node<T>* pNext;
};

#endif //NIBBELS_LISTNODE_H
