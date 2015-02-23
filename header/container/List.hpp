#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

#include "utils/Optional.hpp"
#include "utils/Sanity.hpp"

using namespace std;

template<class T>
struct Node {
    Node(const T& value, Node<T>* next) : value(value), next(next) {}
    T value;
    Node<T>* next;
};

template<class T> class List;

template<class T> class ConstIterator;
template<class T> class Iterator;
#include "container/ConstIterator.hpp"
#include "container/Iterator.hpp"

template<class T>
class List {

protected:
    Node<T>* first;
    Node<T>* last;
    unsigned nbElems;

public:
    List();
    List(const List<T>&);
    ~List();

    /**
     * Adds an element to the list.
     */
    virtual void add(const T&);

    /**
     * Adds all the items contained in the list passed as parameter.
     */
    void addAll(const List&);

    /**
     * Removes all items from the list.
     */
    void clear();

    /**
     * Checks whether the list contains an element matching the provided predicate.
     * The provider parameter must have a test method returning a boolean.
     */
    template<class P>
    bool containsWithPredicate(const P&) const;

    /**
     * Returns the element at the provided index in the list
     */
    T get(unsigned int) const;

    /**
     * Returns an optional value containing the first element of the list
     * matching the provided predicate.
     * The provider parameter must have a test method returning a boolean.
     */
    template<class P>
    Optional<T> getFirstMatching(const P&);

    /**
     * Returns whether the list contains items or not.
     */
    bool isEmpty() const;

    /**
     * Removes the item at the provided position.
     */
    void remove(unsigned);

    /**
     * Returns the current size of the list.
     */
    unsigned size() const;

    List<T>& operator=(List<T>);

    T operator[](unsigned) const;

    friend class ConstIterator<T>;
    friend class Iterator<T>;

};

template<class T>
List<T>::List() {
    this->first = NULL;
    this->last = NULL;
    this->nbElems = 0;
}

template<class T>
List<T>::List(const List<T>& list) {
    this->first = NULL;
    this->last = NULL;
    this->nbElems = 0;

    this->addAll(list);
}

template<class T>
List<T>::~List() {
    this->clear();
}

template<class T>
void List<T>::add(const T& para) {
    // Preparing new node
    Node<T>* tmp = new Node<T>(para, NULL);

    if(!this->first) {
        // Adding first
        this->first = tmp;
        this->last = tmp;
    } else {
        // Adding at the end
        this->last->next = tmp;
        this->last = tmp;
    }
    ++this->nbElems;
}

template<class T>
void List<T>::addAll(const List& toAdd) {
    ConstIterator<T> it(toAdd);
    while(!it.end()) {
        this->add(it++.get());
    }
}

template<class T>
void List<T>::clear() {
    if(this->nbElems == 0) {
        return;
    }

    Node<T>* node = this->first;
    Node<T>* prev;

    while(node) {
        prev = node;
        node = node->next;
        delete prev;
    }
    this->first = NULL;
    this->last = NULL;
    this->nbElems = 0;
}

template<class T>
template<class P>
bool List<T>::containsWithPredicate(const P& predicate) const {
    ConstIterator<T> it(*this);
    while(!it.end()) {
        if(predicate.test(it.get())) {
            return true;
        }
    }
    return false;
}

template<class T>
T List<T>::get(unsigned int index) const {
    Sanity::truthness(index < this->nbElems, "Index out of bounds");

    if(index == 0) {
        return this->first->value;
    }

    ConstIterator<T> it(*this);
    unsigned int i = 0;
    while(true) {
        if(i++ == index) {
            return it;
        }
        ++it;
    }
}

template<class T>
template<class P>
Optional<T> List<T>::getFirstMatching(const P& predicate) {
    Iterator<T> it(*this);
    while(!it.end()) {
        if(predicate.test(it)) {
            return Optional<T>(&it.get());
        }
        ++it;
    }
    return Optional<T>();
}

template<class T>
inline bool List<T>::isEmpty() const {
    return this->nbElems == 0;
}

template<class T>
void List<T>::remove(unsigned index) {
    Sanity::truthness(index < nbElems, "Index must be lower than the list's size");

    Iterator<T> it(*this);

    unsigned i = 0;
    while(i < index) {
        ++i;
        ++it;
    }
    it.remove();
}

template<class T>
inline unsigned List<T>::size() const {
    return this->nbElems;
}

template<class T>
List<T>& List<T>::operator=(List<T> list) {
    swap(this->nbElems, list.nbElems);
    swap(this->first, list.first);
    swap(this->last, list.last);
    return *this;
}

template<class T>
inline T List<T>::operator[](unsigned index) const {
    return this->get(index);
}

#endif
