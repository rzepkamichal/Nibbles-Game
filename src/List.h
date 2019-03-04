#ifndef NIBBELS_LIST_H
#define NIBBELS_LIST_H

#include "Node.h"
#include <iostream>
using namespace std;
template <class T> class List{

private:
    //Wskaźnik na głowę listy typu T
    Node<T>* head;

    //rozmiar listy
    int size;

public:

    /*Konstruktor domyślny.
     *Ustawia wartość head na nullptr.
     *Ustawia wartość size na 0.
     */
    List();

    /*Domyślny destruktor
     *Usuwa elementy listy.
     */
    ~List();

    /*isEmpty
     *zwraca:
     * - true, jeżeli size jest równe zero
     * - false w przeciwnym przypadku
     */
    bool isEmpty();

    /*PushBack
     *Dodaje element o wartości item typu T na koniec listy.
     *Inkrementuje pole size.
     */
    void PushBack(T item);

    /*getNode
     *Zwraca przez referencję obiekt listy o indeksie index.
     */
    T& getNode(int index);

    /*getLast
     *Zwraca przez referencję ostatni obiekt listy.
     */
    T& getLast();

    /*getSize
     *Zwraca wartość size.
     */
    int getSize();
    //void clear();

};

template<class T>
List<T>::List() {
    head = nullptr;
    this->size = 0;
}

template<class T>
bool List<T>::isEmpty() {
    return head == nullptr;
}

template<class T>
void List<T>::PushBack(T item) {

    Node<T>* newNode = new Node<T>();
    newNode->item = item;
    newNode->pNext = nullptr;


    if(isEmpty()){
        head = newNode;
    }else{
        Node<T>* pNode = head;
        while(pNode->pNext){
            pNode = pNode->pNext;
        }

        pNode->pNext = newNode;
    }

    size++;
}

template<class T>
T& List<T>::getNode(int index) {

    Node<T>* pNode = head;
    for(int i=0; i<index;i++){
        pNode = pNode->pNext;
    }

    return pNode->item;
}

template<class T>
List<T>::~List() {

    //cout << "i'm in destructor" << endl;
    Node<T>* pNode = head;
    Node<T>* nextNode;
    while(pNode){
        nextNode = pNode->pNext;
        delete pNode;
        pNode = nextNode;
    }
}

/*

template<class T>
void List<T>::clear() {

    Node<T>* pNode = head;
    Node<T>* nextNode;
    head = nullptr;
    while(pNode){
        nextNode = pNode->pNext;
        delete pNode;
        pNode = nullptr;
        //cout << "node deleted!" << endl;
        pNode = nextNode;
    }
    size = 0;
}*/

template<class T>
int List<T>::getSize() {
    return this->size;
}

template<class T>
T &List<T>::getLast() {

    Node<T>* pNode = head;
    for(int i=0; i<size-1;i++){
        pNode = pNode->pNext;
    }
    return pNode->item;;
}

#endif

