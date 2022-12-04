#ifndef FLASH_GENERIC_ITERATOR_H
#define FLASH_GENERIC_ITERATOR_H

#include <flash/core/Pointer.h>

template<class T>
class Iterator final {
    private:
        RawArrPtr<Pointer<T>>   &_source;
        heap                     _offset;

    public:
        Iterator(RawArrPtr<Pointer<T>> &source, heap offset);
        Iterator(const Iterator<T> &iterator) = default;
       ~Iterator() = default;

    public:
        bool operator==(const Iterator<T> &iterator) const;
        bool operator!=(const Iterator<T> &iterator) const;

        Iterator<T> &operator++(int);
        Iterator<T> &operator++();

    public:
        inline const T *operator->() const;
        inline T *operator->();

        inline const T &operator *() const;
        inline T &operator *();
};

#endif
