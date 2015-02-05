#ifndef SORTEDLIST_HPP
#define SORTEDLIST_HPP

#include "container/List.hpp"

template<class T, class C>
class SortedList : public List<T> {
private:
    C comparator;

public:
    SortedList(const C& comparator) : comparator(comparator) {}
    SortedList(const SortedList& p) : List<T>(p), comparator(p.comparator) {}

    void add(const T&);

    SortedList& operator=(SortedList);
};

template<class T, class C>
void SortedList<T, C>::add(const T& param) {
    Node<T>* newNode = new Node<T>(param, NULL);

    if(!this->first || this->comparator(this->first->value, param) >= 0) {
        newNode->next = this->first;
        this->first = newNode;
        ++this->nbElems;
        return;
    }

    Node<T>* current = this->first->next;
    Node<T>* prec = this->first;
    while(current && this->comparator(current->value, param) < 0) {
        prec = current;
        current = current->next;
    }
    newNode->next = current;
    prec->next = newNode;

    ++this->nbElems;
}

template<class T, class C>
SortedList& SortedList<T, C>::operator=(SortedList l) {
    List<T>::operator=(l);
    this->comparator = l.comparator;
    return *this;
}

#endif
