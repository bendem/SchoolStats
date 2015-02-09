#ifndef SORTEDLIST_HPP
#define SORTEDLIST_HPP

#include "container/List.hpp"

template<class T>
class SortedList : public List<T> {

public:
    SortedList() {}
    SortedList(const SortedList<T>& p) : List<T>(p) {}

    void add(const T&);
};

template<class T>
void SortedList<T>::add(const T& param) {
    Node<T>* newNode = new Node<T>(param, NULL);

    if(!this->first || this->first->value >= param) {
        newNode->next = this->first;
        this->first = newNode;
        ++this->nbElems;
        return;
    }

    Node<T>* current = this->first->next;
    Node<T>* prec = this->first;
    while(current && current->value < param) {
        prec = current;
        current = current->next;
    }
    newNode->next = current;
    prec->next = newNode;

    ++this->nbElems;
}

#endif
