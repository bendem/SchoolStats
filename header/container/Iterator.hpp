#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "container/List.hpp"
#include "utils/Sanity.hpp"

/**
 * Structure allowing to iterate through a BaseList instance.
 *
 * Example usage:
 * ```C++
 * Iterator<Type> iterator(list);
 * while(!it.end()) {
 *     doStuff(it.get());
 *     ++it;
 * }
 * ```
 */
template<class T>
class Iterator {

private:
    List<T>& list;
    Node<T>* current;
    Node<T>* prec;

public:
    Iterator(List<T>&);
    Iterator(const Iterator<T>&);
    ~Iterator();

    /**
    * Checks wether the iterator is pointing at the end of the list.
    *
    * If this returns true, the currently selected element is null!
    */
    bool end();

    /**
    * Resets the position of the iterator in the list to the first element.
    */
    void reset();

    T& get();

    /**
    * Removes the element currently pointed by the iterator from the list.
    */
    T remove();
    Iterator<T>& operator++();
    Iterator<T> operator++(int);
    operator T();
    T& operator &();

    Iterator<T>& operator=(const Iterator<T>&);

};

template<class T>
Iterator<T>::Iterator(List<T>& param)
        : list(param), current(param.first), prec(NULL) {}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& param)
        : list(param.list), current(param.current), prec(param.prec) {}

template<class T>
Iterator<T>::~Iterator() {}

template<class T>
bool Iterator<T>::end() {
    return this->current == NULL;
}

template<class T>
void Iterator<T>::reset() {
    this->current = list.first;
    this->prec = NULL;
}

template<class T>
T& Iterator<T>::get() {
    return this->current->value;
}

template<class T>
T Iterator<T>::remove() {
    T elem(this->current->value);

    if(!this->prec) {
        // Removing first element
        this->list.first = this->current->next;
        delete this->current;
        this->current = this->list.first;
    } else {
        this->prec->next = this->current->next;
        delete this->current;
        this->current = this->prec->next;
    }

    --this->list.nbElems;
    return elem;
}

template<class T>
Iterator<T>& Iterator<T>::operator++() {
    Sanity::nullness(this->current, "Outside of the iterator");

    this->prec = this->current;
    this->current = this->current->next;
    return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int) {
    Sanity::nullness(this->current, "Outside of the iterator");

    Iterator<T> tmp(*this);
    this->prec = this->current;
    this->current = this->current->next;
    return tmp;
}

template<class T>
Iterator<T>::operator T() {
    return this->current->value;
}

template<class T>
T& Iterator<T>::operator&() {
    return this->current->value;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(Iterator<T> const& param) {
    this->list = param.list;
    this->current = param.current;
    this->prec = param.prec;
    return *this;
}


#endif
