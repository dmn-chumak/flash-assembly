#ifndef FLASH_GENERIC_FUNCTION_H
#define FLASH_GENERIC_FUNCTION_H

#include <flash/core/Object.h>

//----------------------------------------
// <Function> class definition
//----------------------------------------

template<class R, class ... V>
class Function : public Object {
    public:
        virtual ~Function() override;
        virtual R call(V... args) const = 0;
};

//----------------------------------------
// <StaticFunction> class definition
//----------------------------------------

template<class R, class ... V>
class StaticFunction final : public Function<R, V...> {
    public:
        using H = R(*)(V...);

    private:
        H _handler;

    public:
        StaticFunction(H handler);
       ~StaticFunction() override;
        R call(V... args) const override;
};

//----------------------------------------
// <MemberFunction> class definition
//----------------------------------------

template<class R, class E, class ... V>
class MemberFunction final : public Function<R, V...> {
    public:
        using H = R(E::*)(V...);

    private:
        E *_element;
        H  _handler;

    public:
        MemberFunction(H handler, E *element);
       ~MemberFunction() override;
        R call(V... args) const override;
};

//----------------------------------------
// <Bindings> class definition
//----------------------------------------

class Bindings final {
    public:
        template<class R, class ... V>
        inline static Function<R, V...> *bind(R (*handler)(V...));

        template<class R, class E, class ... V>
        inline static Function<R, V...> *bind(R (E::*handler)(V...), E *element);
};

#endif
