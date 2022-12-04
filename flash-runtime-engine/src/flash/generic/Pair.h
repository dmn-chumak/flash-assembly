#ifndef FLASH_GENERIC_PAIR_H
#define FLASH_GENERIC_PAIR_H

#include <flash/core/Pointer.h>
#include <flash/core/Object.h>

template<class F, class S>
class Pair final : public Object {
    public:
        Pointer<S> second;
        Pointer<F> first;

    public:
        Pair();
        Pair(const Pair<F, S> &pair);
        Pair(const Pointer<F> &first, const Pointer<S> &second);
        Pair(Pair<F, S> &&pair);
       ~Pair() override;

    public:
        Pair<F, S> &operator=(const Pair<F, S> &pair);
        Pair<F, S> &operator=(Pair<F, S> &&pair);

    public:
        // TODO: Object valueOf() const override;
        String toLocaleString() const override;
        String toString() const override;
};

#endif
