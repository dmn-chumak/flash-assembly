#ifndef FLASH_GENERIC_FUNCTION_CPP
#define FLASH_GENERIC_FUNCTION_CPP

#include <flash/generic/Function.h>
#include <flash/system/Allocator.h>

//----------------------------------------
// <Function> class implementation
//----------------------------------------

template<class R, class ... V>
Function<R, V...>::~Function() {
    // empty
}

//----------------------------------------
// <StaticFunction> class implementation
//----------------------------------------

template<class R, class ... V>
StaticFunction<R, V...>::StaticFunction(H handler)
: _handler(handler) {
    // empty
}

template<class R, class ... V>
StaticFunction<R, V...>::~StaticFunction() {
    _handler = nullptr;
}

template<class R, class ... V>
R StaticFunction<R, V...>::call(V... args) const {
    return (*_handler)(args...);
}

//----------------------------------------
// <MemberFunction> class implementation
//----------------------------------------

template<class R, class E, class ... V>
MemberFunction<R, E, V...>::MemberFunction(H handler, E *element)
: _handler(handler)
, _element(element) {
    // empty
}

template<class R, class E, class ... V>
MemberFunction<R, E, V...>::~MemberFunction() {
    _handler = nullptr;
    _element = nullptr;
}

template<class R, class E, class ... V>
R MemberFunction<R, E, V...>::call(V... args) const {
    return (_element->*_handler)(args...);
}

//----------------------------------------
// <Bindings> class implementation
//----------------------------------------

template<class R, class ... V>
Function<R, V...> *Bindings::bind(R (*handler)(V...)) {
    return new StaticFunction<R, V...>(handler);
}

template<class R, class E, class ... V>
Function<R, V...> *Bindings::bind(R (E::*handler)(V...), E *element) {
    return new MemberFunction<R, E, V...>(handler, element);
}

#endif
