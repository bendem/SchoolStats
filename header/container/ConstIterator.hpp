#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "container/List.hpp"
#include "utils/Sanity.hpp"

/**
 * Structure allowing to iterate through a constant List instance.
 *
 * Example usage:
 * ```C++
 * ConstIterator<Type> iterator(list);
 * while(!it.end()) {
 *     doStuff((Type) it);
 *     ++it;
 * }
 * ```
 */
template<class T>
class ConstIterator {

private:
    const List<T>& list;
    Node<T>* current;

public:
    ConstIterator(const List<T>&);
    ConstIterator(const ConstIterator<T>&);
    ~ConstIterator();

    /**
    * Checks wether the iterator is pointing at the end of the list.
    *
    * If this returns true, the currently selected element is null!
    */
    bool end() const;

    /**
    * Resets the position of the iterator in the list to the first element.
    */
    void reset();

    const T& get() const;

    ConstIterator<T>& operator++();
    ConstIterator<T> operator++(int);
    operator T();
    const T& operator&() const;

};

template<class T>
ConstIterator<T>::ConstIterator(const List<T>& param)
        : list(param), current(param.first) {}

template<class T>
ConstIterator<T>::ConstIterator(const ConstIterator<T>& param)
        : list(param.list), current(param.current) {}

template<class T>
ConstIterator<T>::~ConstIterator() {}

template<class T>
bool ConstIterator<T>::end() const {
    return this->current == NULL;
}

template<class T>
void ConstIterator<T>::reset() {
    this->current = list.first;
}

template<class T>
const T& ConstIterator<T>::get() const {
    return this->current->value;
}

template<class T>
ConstIterator<T>& ConstIterator<T>::operator++() {
    Sanity::nullness(this->current, "Outside of the list");

    this->current = this->current->next;
    return *this;
}

template<class T>
ConstIterator<T> ConstIterator<T>::operator++(int) {
    Sanity::nullness(this->current, "Outside of the list");

    ConstIterator<T> tmp(*this);
    this->current = this->current->next;
    return tmp;
}

template<class T>
ConstIterator<T>::operator T() {
    return this->current->value;
}

template<class T>
const T& ConstIterator<T>::operator&() const {
    return this->current->value;
}

#endif
