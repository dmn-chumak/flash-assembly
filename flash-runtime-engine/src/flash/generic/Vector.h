#ifndef FLASH_GENERIC_VECTOR_H
#define FLASH_GENERIC_VECTOR_H

#include <flash/core/Iterator.h>
#include <flash/core/Object.h>

template<class T>
class Vector : public Object {
    private:
        RawArrPtr<T>    _source;
        heap            _capacity;
        heap            _length;

    public:
        Vector();
        Vector(const heap capacity, T *source);
        Vector(const heap capacity);
        Vector(const Vector<T> &array);
        Vector(Vector<T> &&array);
       ~Vector() override;

    public:
        Vector<T> &operator=(const Vector<T> &array);
        Vector<T> &operator=(Vector<T> &&array);

        const T &operator[](const heap index) const;
        T &operator[](const heap index);

        heap length(const heap length);
        heap length() const;

        const T *source() const;
        T *source();

    public:
        sInt lastIndexOf(T element, const heap startIndex = 0) const;
        sInt indexOf(T element, const heap startIndex = 0) const;

        heap insertAt(const heap index, T element);
        heap insertFirst(T element);
        heap insertLast(T element);

        T obtainAt(const heap index) const;
        T obtainFirst() const;
        T obtainLast() const;

        T removeAt(const heap index);
        T removeFirst();
        T removeLast();

        Pointer<Vector<T>> combine(const Pointer<Vector<T>> &source) const;
        Pointer<Vector<T>> reverse() const;
        String implode(const String &separator) const;

        String toLocaleString() const override;
        String toString() const override;

        Iterator<T> begin();
        Iterator<T> end();

    private:
        void releaseContent(const heap startIndex);
        void moveContent(const heap startIndex, const sInt offset = 1);
        void ensureCapacity(const heap capacity);
        void copyFrom(const Vector<T> &array);
};

#endif
