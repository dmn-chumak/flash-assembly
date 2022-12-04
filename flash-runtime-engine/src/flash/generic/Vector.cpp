#ifndef FLASH_GENERIC_VECTOR_CPP
#define FLASH_GENERIC_VECTOR_CPP

#include <flash/utils/Constant.h>
#include <flash/generic/Vector.h>
#include <flash/system/Allocator.h>
#include <flash/core/Utils.h>
#include <flash/language/String.h>

template<class T>
Vector<T>::Vector()
: _capacity(0)
, _length(0) {
    // empty
}

template<class T>
Vector<T>::Vector(const heap capacity, T *source)
: _source(source)
, _capacity(capacity)
, _length(capacity) {
    // empty
}

template<class T>
Vector<T>::Vector(const heap capacity)
: _source(capacity)
, _capacity(capacity)
, _length(0) {
    // empty
}

template<class T>
Vector<T>::Vector(const Vector &array) {
    copyFrom(array);
}

template<class T>
Vector<T>::Vector(Vector &&array)
: _source(Utils::move(array._source))
, _capacity(array._capacity)
, _length(array._length) {
    // empty
}

template<class T>
Vector<T>::~Vector() {
    // empty
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &array){
    copyFrom(array);
    return *this;
}

template<class T>
Vector<T> &Vector<T>::operator=(Vector &&array) {
    _source = Utils::move(array._source);
    _capacity = array._capacity;
    _length = array._length;
}

template<class T>
const T &Vector<T>::operator[](const heap index) const {
    return _source[index];
}

template<class T>
T &Vector<T>::operator[](const heap index) {
    if (index >= _length) {
        ensureCapacity(index + 1);
        _length = index + 1;
    }

    return _source[index];
}

template<class T>
heap Vector<T>::length(const heap length) {
    if (length < _length) {
        releaseContent(length);
    } else if (length > _length) {
        ensureCapacity(length);
    }

    return _length = length;
}

template<class T>
heap Vector<T>::length() const {
    return _length;
}

template<class T>
const T *Vector<T>::source() const {
    return _source.get();
}

template<class T>
T *Vector<T>::source() {
    return _source.get();
}

template<class T>
sInt Vector<T>::lastIndexOf(T element, const heap startIndex) const {
    const heap realStartIndex = (startIndex == 0) ? (_length - 1) : startIndex;

    for (sInt index = realStartIndex; index >= 0; --index) {
        if (_source[index] == element) {
            return static_cast<sInt>(index);
        }
    }

    return INVALID_INDEX;
}

template<class T>
sInt Vector<T>::indexOf(T element, const heap startIndex) const {
    for (sInt index = startIndex; index < _length; ++index) {
        if (_source[index] == element) {
            return static_cast<sInt>(index);
        }
    }

    return INVALID_INDEX;
}

template<class T>
heap Vector<T>::insertAt(const heap index, T element) {
    heap length = 0;

    if (index < _length) {
        length = _length + 1;
    } else {
        length = index + 1;
    }

    // TODO: fix redundant moving array source twice
    ensureCapacity(length);
    moveContent(index);
    _source[index] = element;

    return _length = length;
}

template<class T>
heap Vector<T>::insertFirst(T element) {
    return insertAt(0, element);
}

template<class T>
heap Vector<T>::insertLast(T element) {
    return insertAt(_length, element);
}

template<class T>
T Vector<T>::obtainAt(const heap index) const {
    return _source[index];
}

template<class T>
T Vector<T>::obtainFirst() const {
    return obtainAt(0);
}

template<class T>
T Vector<T>::obtainLast() const {
    return obtainAt(_length - 1);
}

template<class T>
T Vector<T>::removeAt(const heap index) {
    if (index >= _length) {
        return nullptr;
    }

    T element = _source[index];
    moveContent(index + 1, -1);
    _source[--_length] = nullptr;

    return element;
}

template<class T>
T Vector<T>::removeFirst() {
    return removeAt(0);
}

template<class T>
T Vector<T>::removeLast() {
    return removeAt(_length - 1);
}

template<class T>
Pointer<Vector<T>> Vector<T>::combine(const Pointer<Vector<T>> &source) const {
    Pointer<Vector<T>> result = new Vector<T>(_length + source->_length);
    result->_length = _length + source->_length;

    Utils::copy(
        _source.get(),
        _source.get() + _length,
        result->_source.get()
    );

    Utils::copy(
        source->_source.get(),
        source->_source.get() + source->_length,
        result->_source.get() + _length
    );

    return result;
}

template<class T>
Pointer<Vector<T>> Vector<T>::reverse() const {
    Pointer<Vector<T>> result = new Vector<T>(_length);
    result->_length = _length;

    for (heap index = 0; index < _length; index++) {
        result->_source[_length - index - 1] = _source[index];
    }

    return result;
}

template<class T>
String Vector<T>::implode(const String &separator) const {
    String result = "";

    for (heap index = 0; index < _length; ++index) {
        if (index > 0) result += separator;
        result += _source[index];
    }

    return result;
}

template<class T>
String Vector<T>::toLocaleString() const {
    // TODO: take into account current locale
    return toString();
}

template<class T>
String Vector<T>::toString() const {
    return "[ " + implode(", ") + " ]";
}

template<class T>
Iterator<T> Vector<T>::begin() {
    return Iterator<T>(_source, 0);
}

template<class T>
Iterator<T> Vector<T>::end() {
    return Iterator<T>(_source, _length);
}

template<class T>
void Vector<T>::releaseContent(const heap startIndex) {
    for (heap index = startIndex; index < _length; ++index) {
        _source[index] = 0;
    }
}

template<class T>
void Vector<T>::moveContent(const heap startIndex, const sInt offset) {
    if (startIndex >= _length) {
        return;
    }

    if (offset > 0) {
        for (heap index = _length + offset - 1; index > startIndex; --index) {
            _source[index] = Utils::move(_source[index - offset]);
        }
    } else {
        for (heap index = startIndex; index < _length; ++index) {
            _source[index] = Utils::move(_source[index - offset]);
        }
    }
}

template<class T>
void Vector<T>::ensureCapacity(const heap capacity) {
    if (_capacity >= capacity) {
        return;
    }

    const RawArrPtr<T> temporary = Utils::move(_source);
    _capacity = capacity;
    _source = new T[_capacity];

    if (temporary != nullptr) {
        Utils::move(
            temporary.get(),
            temporary.get() + _length,
            _source.get()
        );
    }
}

template<class T>
void Vector<T>::copyFrom(const Vector<T> &array) {
    _capacity = array._length;
    _source = new T[_length];
    _length = array._length;

    Utils::copy(
        array._source.get(),
        array._source.get() + _length,
        _source.get()
    );
}

#endif
