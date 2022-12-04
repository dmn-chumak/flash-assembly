#ifndef FLASH_GENERIC_POINTER_H
#define FLASH_GENERIC_POINTER_H

#include <flash/core/Type.h>

//----------------------------------------
// <Pointer> class definition
//----------------------------------------

template<class T>
class Pointer final {
    private:
        T *_object;

    public:
        Pointer();
        Pointer(T *object);
        Pointer(const Pointer<T> &pointer);

        template<class O> Pointer(const Pointer<O> &pointer);
        Pointer(Pointer<T> &&pointer);
        template<class O> Pointer(Pointer<O> &&pointer);
       ~Pointer();

    public:
        Pointer<T> &operator=(T *object);
        Pointer<T> &operator=(const Pointer<T> &pointer);
        template<class O> Pointer<T> &operator=(const Pointer<O> &pointer);
        Pointer<T> &operator=(Pointer<T> &&pointer);
        template<class O> Pointer<T> &operator=(Pointer<O> &&pointer);

        bool operator==(null) const;
        bool operator==(const T *object) const;
        template<class O> bool operator==(const O *object) const;
        bool operator==(const Pointer<T> &pointer) const;
        template<class O> bool operator==(const Pointer<O> &pointer) const;

        template<class O> friend bool operator==(null, const Pointer<O> &pointer);
        template<class O> friend bool operator==(const O *object, const Pointer<O> &pointer);
        template<class O, class S> friend bool operator==(const O *object, const Pointer<S> &pointer);

        bool operator!=(null) const;
        bool operator!=(const T *object) const;
        template<class O> bool operator!=(const O *object) const;
        bool operator!=(const Pointer<T> &pointer) const;
        template<class O> bool operator!=(const Pointer<O> &pointer) const;

        template<class O> friend bool operator!=(null, const Pointer<O> &pointer);
        template<class O> friend bool operator!=(const O *object, const Pointer<O> &pointer);
        template<class O, class S> friend bool operator!=(const O *object, const Pointer<S> &pointer);

    public:
        const T *operator->() const;
        const T &operator *() const;

        T *operator->();
        T &operator *();

        operator T const *() const;
        operator T *();

        T *object() const;

    private:
        void setRefObject(T *object);
        void incRefCount();
        void decRefCount();

    private:
        template<class>
        friend class Pointer;
};

//----------------------------------------
// <RawObjPtr> class definition
//----------------------------------------

template<class T>
class RawObjPtr final {
    private:
        T *_object;

    public:
        RawObjPtr();
        RawObjPtr(T *object);
        RawObjPtr(const RawObjPtr<T> &pointer) = delete;
        RawObjPtr(RawObjPtr<T> &&pointer);
       ~RawObjPtr();

    public:
        RawObjPtr<T> &operator=(null);
        RawObjPtr<T> &operator=(T *object);
        RawObjPtr<T> &operator=(const RawObjPtr<T> &pointer) = delete;
        RawObjPtr<T> &operator=(RawObjPtr<T> &&pointer);

        bool operator==(null) const;
        bool operator==(const T *object) const;
        bool operator==(const RawObjPtr<T> &pointer) = delete;

        template<class O> friend bool operator==(null, const RawObjPtr<O> &pointer);
        template<class O> friend bool operator==(const O *object, const RawObjPtr<O> &pointer);

        bool operator!=(null) const;
        bool operator!=(const T *object) const;
        bool operator!=(const RawObjPtr<T> &pointer) = delete;

        template<class O> friend bool operator!=(null, const RawObjPtr<O> &pointer);
        template<class O> friend bool operator!=(const O *object, const RawObjPtr<O> &pointer);

    public:
        inline const T *operator->() const;
        inline T *operator->();

        inline const T &operator *() const;
        inline T &operator *();

        inline const T *get() const;
        inline T *get();

    public:
        void set(T *object);
};

//----------------------------------------
// <RawArrPtr> class definition
//----------------------------------------

template<class T>
class RawArrPtr final {
    private:
        T *_object;

    public:
        RawArrPtr();
        RawArrPtr(T *object);
        RawArrPtr(const heap capacity);
        RawArrPtr(const RawArrPtr<T> &pointer) = delete;
        RawArrPtr(RawArrPtr<T> &&pointer);
       ~RawArrPtr();

    public:
        RawArrPtr<T> &operator=(null);
        RawArrPtr<T> &operator=(T *object);
        RawArrPtr<T> &operator=(const RawArrPtr<T> &pointer) = delete;
        RawArrPtr<T> &operator=(RawArrPtr<T> &&pointer);

        bool operator==(null) const;
        bool operator==(const T *object) const;
        bool operator==(const RawArrPtr<T> &pointer) = delete;

        template<class O> friend bool operator==(null, const RawArrPtr<O> &pointer);
        template<class O> friend bool operator==(const O *object, const RawArrPtr<O> &pointer);

        bool operator!=(null) const;
        bool operator!=(const T *object) const;
        bool operator!=(const RawArrPtr<T> &pointer) = delete;

        template<class O> friend bool operator!=(null, const RawArrPtr<O> &pointer);
        template<class O> friend bool operator!=(const O *object, const RawArrPtr<O> &pointer);

    public:
        inline const T &operator[](const heap index) const;
        inline T &operator[](const heap index);

        inline const T *get() const;
        inline T *get();

    public:
        void set(T *object);
};

#endif
