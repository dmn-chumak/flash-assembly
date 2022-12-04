#ifndef FLASH_GENERIC_HASH_MAP_H
#define FLASH_GENERIC_HASH_MAP_H

#include <flash/core/Iterator.h>
#include <flash/core/Pair.h>
#include <flash/core/Array.h>

template<class K, class V>
class HashMap : public Object {
    private:
        Array<Pair<K, V>> _source;

    public:
        HashMap();
        HashMap(const HashMap<K, V> &map);
        HashMap(HashMap<K, V> &&map);
       ~HashMap() override;

    public:
        HashMap<K, V> &operator=(const HashMap<K, V> &map);
        HashMap<K, V> &operator=(HashMap<K, V> &&map);

        const Pointer<V> &operator[](const Pointer<K> &key)const;
        Pointer<V> &operator[](const Pointer<K> &key);

        heap length() const;

    public:
        void insertByKey(const Pointer<K> &key, const Pointer<V> &value);
        Pointer<V> removeByKey(const Pointer<K> &key);
        Pointer<V> obtainByKey(const Pointer<K> &key);

        String toLocaleString() const override;
        String toString() const override;

        Iterator<Pair<K, V>> begin();
        Iterator<Pair<K, V>> end();

    private:
        sInt indexOf(const Pointer<K> &key) const;
};

#endif
