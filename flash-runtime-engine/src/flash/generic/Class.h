#ifndef FLASH_GENERIC_CLASS_H
#define FLASH_GENERIC_CLASS_H

#include <flash/core/Object.h>

template<class T>
class Class final : public Object {
    public:
        Class();
       ~Class() override;
};

#endif
