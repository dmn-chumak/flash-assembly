#ifndef FLASH_GENERIC_ARRAY_H
#define FLASH_GENERIC_ARRAY_H

#include <flash/core/Iterator.h>
#include <flash/core/Object.h>

template<class T>
class Array : public Object {
    private:
        RawArrPtr<Pointer<T>>   _source;
        heap                    _capacity;
        heap                    _length;

    public:
        Array();
        Array(const heap capacity);
        Array(const Array<T> &array);
        Array(Array<T> &&array);
       ~Array() override;

    public:
        Array<T> &operator=(const Array<T> &array);
        Array<T> &operator=(Array<T> &&array);

        const Pointer<T> &operator[](const heap index) const;
        Pointer<T> &operator[](const heap index);

        heap length(const heap length);
        heap length() const;

    public:
        sInt lastIndexOf(const Pointer<T> &element, const heap startIndex = 0) const;
        sInt indexOf(const Pointer<T> &element, const heap startIndex = 0) const;

        heap insertAt(const heap index, const Pointer<T> &element);
        heap insertFirst(const Pointer<T> &element);
        heap insertLast(const Pointer<T> &element);

        Pointer<T> obtainAt(const heap index);
        Pointer<T> obtainFirst();
        Pointer<T> obtainLast();

        Pointer<T> removeAt(const heap index);
        Pointer<T> removeFirst();
        Pointer<T> removeLast();

        Pointer<Array<T>> combine(const Pointer<Array<T>> &source) const;
        Pointer<Array<T>> reverse() const;
        String implode(const String &separator) const;

        String toLocaleString() const override;
        String toString() const override;

        Iterator<T> begin();
        Iterator<T> end();

    private:
        void releaseContent(const heap startIndex);
        void moveContent(const heap startIndex, const sInt offset = 1);
        void ensureCapacity(const heap capacity);
        void copyFrom(const Array<T> &array);
};

#endif
