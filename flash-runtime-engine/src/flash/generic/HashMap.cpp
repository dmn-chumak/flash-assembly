#ifndef FLASH_GENERIC_HASH_MAP_CPP
#define FLASH_GENERIC_HASH_MAP_CPP

#include <flash/utils/Constant.h>
#include <flash/generic/HashMap.h>
#include <flash/system/Allocator.h>
#include <flash/core/Utils.h>

template<class K, class V>
HashMap<K, V>::HashMap() {
    // empty
}

template<class K, class V>
HashMap<K, V>::HashMap(const HashMap<K, V> &map)
: _source(map._source) {
    // empty
}

template<class K, class V>
HashMap<K, V>::HashMap(HashMap<K, V> &&map)
: _source(Utils::move(map._source)) {
    // empty
}

template<class K, class V>
HashMap<K, V>::~HashMap() {
    // empty
}

template<class K, class V>
HashMap<K, V> &HashMap<K, V>::operator=(const HashMap<K, V> &map) {
    _source = map._source;
}

template<class K, class V>
HashMap<K, V> &HashMap<K, V>::operator=(HashMap<K, V> &&map) {
    _source = Utils::move(map._source);
}

template<class K, class V>
const Pointer<V> &HashMap<K, V>::operator[](const Pointer<K> &key) const {
    const sInt index = indexOf(key);

    if (index != INVALID_INDEX) {
        return _source[index]->second;
    }

    return nullptr;
}

template<class K, class V>
Pointer<V> &HashMap<K, V>::operator[](const Pointer<K> &key) {
    const sInt index = indexOf(key);

    if (index != INVALID_INDEX) {
        return _source[index]->second;
    }

    Pointer<Pair<K, V>> pair = new Pair<K, V>(key, nullptr);
    _source.insertLast(pair);

    return pair->second;
}

template<class K, class V>
heap HashMap<K, V>::length() const {
    return _source.length();
}

template<class K, class V>
void HashMap<K, V>::insertByKey(const Pointer<K> &key, const Pointer<V> &value) {
    const sInt index = indexOf(key);

    if (index != INVALID_INDEX) {
        _source[index]->second = value;
        return;
    }

    _source.insertLast(
        new Pair<K, V>(key, value)
    );
}

template<class K, class V>
Pointer<V> HashMap<K, V>::removeByKey(const Pointer<K> &key) {
    const sInt index = indexOf(key);

    if (index != INVALID_INDEX) {
        return _source.removeAt(static_cast<const heap>(index))->second;
    }

    return nullptr;
}

template<class K, class V>
Pointer<V> HashMap<K, V>::obtainByKey(const Pointer<K> &key) {
    const sInt index = indexOf(key);

    if (index != INVALID_INDEX) {
        return _source[index]->second;
    }

    return nullptr;
}

template<class K, class V>
String HashMap<K, V>::toLocaleString() const {
    // TODO: take into account current locale
    return toString();
}

template<class K, class V>
String HashMap<K, V>::toString() const {
    return "{ " + _source.implode(", ") + " }";
}

template<class K, class V>
Iterator<Pair<K, V>> HashMap<K, V>::begin() {
    return _source.begin();
}

template<class K, class V>
Iterator<Pair<K, V>> HashMap<K, V>::end() {
    return _source.end();
}

template<class K, class V>
sInt HashMap<K, V>::indexOf(const Pointer<K> &key) const {
    const heap length = _source.length();

    for (heap index = 0; index < length; ++index) {
        if (_source[index]->first == key) {
            return static_cast<sInt>(index);
        }
    }

    return INVALID_INDEX;
}

#endif
