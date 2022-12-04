#ifndef FLASH_GENERIC_POINTER_CPP
#define FLASH_GENERIC_POINTER_CPP

#include <flash/generic/Pointer.h>
#include <flash/system/Allocator.h>
#include <flash/core/Utils.h>

//----------------------------------------
// <Pointer> class implementation
//----------------------------------------

template<class T>
Pointer<T>::Pointer()
: _object(nullptr) {
    // empty
}

template<class T>
Pointer<T>::Pointer(T *object)
: _object(object) {
    incRefCount();
}

template<class T>
Pointer<T>::Pointer(const Pointer<T> &pointer)
: _object(pointer._object) {
    incRefCount();
}

template<class T>
template<class O>
Pointer<T>::Pointer(const Pointer<O> &pointer)
: _object(dynamic_cast<T *>(pointer._object)) {
    incRefCount();
}

template<class T>
Pointer<T>::Pointer(Pointer<T> &&pointer)
: _object(pointer._object) {
    pointer._object = nullptr;
}

template<class T>
template<class O>
Pointer<T>::Pointer(Pointer<O> &&pointer)
: _object(dynamic_cast<T *>(pointer._object)) {
    pointer._object = nullptr;
}

template<class T>
Pointer<T>::~Pointer() {
    decRefCount();
}

template<class T>
Pointer<T> &Pointer<T>::operator=(T *object) {
    if (_object != object) {
        setRefObject(object);
    }

    return *this;
}

template<class T>
Pointer<T> &Pointer<T>::operator=(const Pointer<T> &pointer) {
    if (this != &pointer) {
        setRefObject(pointer._object);
    }

    return *this;
}

template<class T>
template<class O>
Pointer<T> &Pointer<T>::operator=(const Pointer<O> &pointer) {
    if (this != &pointer) {
        setRefObject(dynamic_cast<T *>(pointer._object));
    }

    return *this;
}

template<class T>
Pointer<T> &Pointer<T>::operator=(Pointer<T> &&pointer) {
    if (this != &pointer) {
        decRefCount();
        _object = pointer._object;
        pointer._object = nullptr;
    }

    return *this;
}

template<class T>
template<class O>
Pointer<T> &Pointer<T>::operator=(Pointer<O> &&pointer) {
    if (this != &pointer) {
        decRefCount();
        _object = dynamic_cast<T *>(pointer._object);
        pointer._object = nullptr;
    }

    return *this;
}

template<class T>
bool Pointer<T>::operator==(null) const {
    return _object == nullptr;
}

template<class T>
bool Pointer<T>::operator==(const T *object) const {
    return Utils::equals(_object, object);
}

template<class T>
template<class O>
bool Pointer<T>::operator==(const O *object) const {
    return Utils::equals(_object, object);
}

template<class T>
bool Pointer<T>::operator==(const Pointer<T> &pointer) const {
    return Utils::equals(_object, pointer._object);
}

template<class T>
template<class O>
bool Pointer<T>::operator==(const Pointer<O> &pointer) const {
    return Utils::equals(_object, pointer._object);
}

template<class O>
bool operator==(null, const Pointer<O> &pointer) {
    return nullptr == pointer._object;
}

template<class O>
bool operator==(const O *object, const Pointer<O> &pointer) {
    return Utils::equals(object, pointer._object);
}

template<class O, class S>
bool operator==(const O *object, const Pointer<S> &pointer) {
    return Utils::equals(object, pointer._object);
}

template<class T>
bool Pointer<T>::operator!=(null) const {
    return _object != nullptr;
}

template<class T>
bool Pointer<T>::operator!=(const T *object) const {
    return !Utils::equals(_object, object);
}

template<class T>
template<class O>
bool Pointer<T>::operator!=(const O *object) const {
    return !Utils::equals(_object, object);
}

template<class T>
bool Pointer<T>::operator!=(const Pointer<T> &pointer) const {
    return !Utils::equals(_object, pointer._object);
}

template<class T>
template<class O>
bool Pointer<T>::operator!=(const Pointer<O> &pointer) const {
    return !Utils::equals(_object, pointer._object);
}

template<class O>
bool operator!=(null, const Pointer<O> &pointer) {
    return nullptr != pointer._object;
}

template<class O>
bool operator!=(const O *object, const Pointer<O> &pointer) {
    return !Utils::equals(object, pointer._object);
}

template<class O, class S>
bool operator!=(const O *object, const Pointer<S> &pointer) {
    return !Utils::equals(object, pointer._object);
}

template<class T>
const T *Pointer<T>::operator->() const {
    return _object;
}

template<class T>
const T &Pointer<T>::operator *() const {
    return *_object;
}

template<class T> T *Pointer<T>::operator->() {
    return _object;
}

template<class T>
T &Pointer<T>::operator *() {
    return *_object;
}

template<class T>
Pointer<T>::operator T const *() const {
    return _object;
}

template<class T>
Pointer<T>::operator T *() {
    return _object;
}

template<class T>
T *Pointer<T>::object() const {
    return _object;
}

template<class T>
void Pointer<T>::setRefObject(T *object) {
    decRefCount();
    _object = object;
    incRefCount();
}

template<class T>
void Pointer<T>::incRefCount() {
    if (_object != nullptr) {
        _object->_refCount++;
    }
}

template<class T>
void Pointer<T>::decRefCount() {
    if (_object == nullptr) {
        return;
    }

    if (--_object->_refCount > 0) {
        return;
    }

    delete _object;
    _object = nullptr;
}

//----------------------------------------
// <RawObjPtr> class implementation
//----------------------------------------

template<class T>
RawObjPtr<T>::RawObjPtr()
: _object(nullptr) {
    // empty
}

template<class T>
RawObjPtr<T>::RawObjPtr(T *object)
: _object(object) {
    // empty
}

template<class T>
RawObjPtr<T>::RawObjPtr(RawObjPtr <T> &&pointer)
: _object(pointer._object) {
    pointer._object = nullptr;
}

template<class T>
RawObjPtr<T>::~RawObjPtr() {
    set(nullptr);
}

template<class T>
RawObjPtr<T> &RawObjPtr<T>::operator=(null) {
    set(nullptr);
    return *this;
}

template<class T>
RawObjPtr<T> &RawObjPtr<T>::operator=(T *object) {
    set(object);
    return *this;
}

template<class T>
RawObjPtr<T> &RawObjPtr<T>::operator=(RawObjPtr<T> &&pointer) {
    set(pointer._object);
    pointer._object = nullptr;
    return *this;
}

template<class T>
bool RawObjPtr<T>::operator==(null) const {
    return _object == nullptr;
}

template<class T>
bool RawObjPtr<T>::operator==(const T *object) const {
    return _object == object;
}

template<class O>
bool operator==(null, const RawObjPtr<O> &pointer) {
    return nullptr == pointer._object;
}

template<class O>
bool operator==(const O *object, const RawObjPtr<O> &pointer) {
    return object == pointer._object;
}

template<class T>
bool RawObjPtr<T>::operator!=(null) const {
    return _object != nullptr;
}

template<class T>
bool RawObjPtr<T>::operator!=(const T *object) const {
    return _object != object;
}

template<class O>
bool operator!=(null, const RawObjPtr<O> &pointer) {
    return nullptr != pointer._object;
}

template<class O>
bool operator!=(const O *object, const RawObjPtr<O> &pointer) {
    return object != pointer._object;
}

template<class T>
const T *RawObjPtr<T>::operator->() const {
    return _object;
}

template<class T>
T *RawObjPtr<T>::operator->() {
    return _object;
}

template<class T>
const T &RawObjPtr<T>::operator*() const {
    return *_object;
}

template<class T>
T &RawObjPtr<T>::operator*() {
    return *_object;
}

template<class T>
const T *RawObjPtr<T>::get() const {
    return _object;
}

template<class T>
T *RawObjPtr<T>::get() {
    return _object;
}

template<class T>
void RawObjPtr<T>::set(T *object) {
    if (_object != nullptr) {
        delete _object;
    }

    _object = object;
}

//----------------------------------------
// <RawArrPtr> class implementation
//----------------------------------------

template<class T>
RawArrPtr<T>::RawArrPtr()
: _object(nullptr) {
    // empty
}

template<class T>
RawArrPtr<T>::RawArrPtr(T *object)
: _object(object) {
    // empty
}

template<class T>
RawArrPtr<T>::RawArrPtr(const heap capacity)
: _object(new T[capacity]) {
    // empty
}

template<class T>
RawArrPtr<T>::RawArrPtr(RawArrPtr <T> &&pointer)
: _object(pointer._object) {
    pointer._object = nullptr;
}

template<class T>
RawArrPtr<T>::~RawArrPtr() {
    set(nullptr);
}

template<class T>
RawArrPtr<T> &RawArrPtr<T>::operator=(null) {
    set(nullptr);
    return *this;
}

template<class T>
RawArrPtr<T> &RawArrPtr<T>::operator=(T *object) {
    set(object);
    return *this;
}

template<class T>
RawArrPtr<T> &RawArrPtr<T>::operator=(RawArrPtr<T> &&pointer) {
    set(pointer._object);
    pointer._object = nullptr;
    return *this;
}

template<class T>
bool RawArrPtr<T>::operator==(null) const {
    return _object == nullptr;
}

template<class T>
bool RawArrPtr<T>::operator==(const T *object) const {
    return _object == object;
}

template<class O>
bool operator==(null, const RawArrPtr<O> &pointer) {
    return nullptr == pointer._object;
}

template<class O>
bool operator==(const O *object, const RawArrPtr<O> &pointer) {
    return object == pointer._object;
}

template<class T>
bool RawArrPtr<T>::operator!=(null) const {
    return _object != nullptr;
}

template<class T>
bool RawArrPtr<T>::operator!=(const T *object) const {
    return _object != object;
}

template<class O>
bool operator!=(null, const RawArrPtr<O> &pointer) {
    return nullptr != pointer._object;
}

template<class O>
bool operator!=(const O *object, const RawArrPtr<O> &pointer) {
    return object != pointer._object;
}

template<class T>
const T &RawArrPtr<T>::operator[](const heap index) const {
    return _object[index];
}

template<class T>
T &RawArrPtr<T>::operator[](const heap index) {
    return _object[index];
}

template<class T>
const T *RawArrPtr<T>::get() const {
    return _object;
}

template<class T>
T *RawArrPtr<T>::get() {
    return _object;
}

template<class T>
void RawArrPtr<T>::set(T *object) {
    if (_object != nullptr) {
        delete [] _object;
    }

    _object = object;
}

#endif
