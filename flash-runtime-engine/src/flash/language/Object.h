#ifndef FLASH_LANGUAGE_OBJECT_H
#define FLASH_LANGUAGE_OBJECT_H

#include <flash/core/Type.h>

class String;

class Object {
    public:
        uByte _refCount;

    public:
        Object();
        virtual ~Object();

    public:
        virtual bool operator==(const Object &object) const;
        virtual bool operator!=(const Object &object) const;
        virtual String toLocaleString() const;
        virtual String toString() const;

    private:
        template<class>
        friend class Pointer;
};

#endif
