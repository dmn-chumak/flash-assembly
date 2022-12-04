#ifndef FLASH_GENERIC_PAIR_CPP
#define FLASH_GENERIC_PAIR_CPP

#include <flash/generic/Pair.h>
#include <flash/core/Utils.h>

template<class F, class S>
Pair<F, S>::Pair() {
    // empty
}

template<class F, class S>
Pair<F, S>::Pair(const Pair<F, S> &pair)
: second(pair.second)
, first(pair.first) {
    // empty
}

template<class F, class S>
Pair<F, S>::Pair(const Pointer<F> &first, const Pointer<S> &second)
: second(second)
, first(first) {
    // empty
}

template<class F, class S>
Pair<F, S>::Pair(Pair<F, S> &&pair)
: second(Utils::move(pair.second))
, first(Utils::move(pair.first)) {
    // empty
}

template<class F, class S>
Pair<F, S>::~Pair() {
    // empty
}

template<class F, class S>
Pair<F, S> &Pair<F, S>::operator=(const Pair<F, S> &pair) {
    second = pair.second;
    first = pair.first;
    return *this;
};

template<class F, class S>
Pair<F, S> &Pair<F, S>::operator=(Pair<F, S> &&pair) {
    second = Utils::move(pair.second);
    first = Utils::move(pair.first);
    return *this;
}

template<class F, class S>
String Pair<F, S>::toLocaleString() const {
    // TODO: take into account current locale
    return toString();
}

template<class F, class S>
String Pair<F, S>::toString() const {
    String result = "";

    result += first;
    result += ": ";
    result += second;

    return result;
}

#endif
