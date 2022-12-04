#ifndef FLASH_GENERIC_ITERATOR_CPP
#define FLASH_GENERIC_ITERATOR_CPP

#include <flash/generic/Iterator.h>

template<class T>
Iterator<T>::Iterator(RawArrPtr<Pointer<T>> &source, heap offset)
: _source(source)
, _offset(offset) {
    // empty
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T> &iterator) const {
    return _offset == iterator._offset;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T> &iterator) const {
    return _offset != iterator._offset;
}

template<class T>
Iterator<T> &Iterator<T>::operator++(int) {
    ++_offset;
    return *this;
}

template<class T>
Iterator<T> &Iterator<T>::operator++() {
    Iterator<T> result = *this;
    ++_offset;
    return result;
}

template<class T>
const T *Iterator<T>::operator->() const {
    return &(*_source[_offset]);
}

template<class T>
T *Iterator<T>::operator->() {
    return &(*_source[_offset]);
}

template<class T>
const T &Iterator<T>::operator*() const {
    return _source[_offset];
}

template<class T>
T &Iterator<T>::operator*() {
    return _source[_offset];
}

#endif
