#ifndef FLASH_LANGUAGE_STRING_H
#define FLASH_LANGUAGE_STRING_H

#include <flash/language/Object.h>
#include <flash/core/Pointer.h>

/**
 * String can take three states:
 * - null-empty string that doesn't allocated any bytes of memory (== nullptr)
 * - empty string with length = 0, that contains only '\0' byte (== "")
 * - non-empty string with length > 0, that contains null-terminated byte array (!= "" && != nullptr)
 */
class String : public Object {
    private:
        RawArrPtr<sChar>    _source;
        heap                _length;

    public:
        String();
        String(null);
        String(const sByte value);
        String(const sChar value);
        String(const sByte *bytes);
        String(const sByte *bytes, const heap length);
        String(const sChar *chars);
        String(const sChar *chars, const heap length);
        String(const String &string);
        String(String &&string);
       ~String() override;

    public:
        String operator+(const sInt value) const;
        String operator+(const uInt value) const;
        String operator+(const sByte value) const;
        String operator+(const uByte value) const;
        String operator+(const sLong value) const;
        String operator+(const uLong value) const;
        String operator+(const float value) const;
        String operator+(const double value) const;
        String operator+(const sShort value) const;
        String operator+(const uShort value) const;

        String operator+(null) const;
        String operator+(const sByte *bytes) const;
        String operator+(const sChar *chars) const;
        String operator+(const String &string) const;
        String operator+(const Object &object) const;
        String operator+(const Pointer<Object> &pointer) const;

        friend String operator+(const sInt value, const String &string);
        friend String operator+(const uInt value, const String &string);
        friend String operator+(const sByte value, const String &string);
        friend String operator+(const uByte value, const String &string);
        friend String operator+(const sLong value, const String &string);
        friend String operator+(const uLong value, const String &string);
        friend String operator+(const float value, const String &string);
        friend String operator+(const double value, const String &string);
        friend String operator+(const sShort value, const String &string);
        friend String operator+(const uShort value, const String &string);

        friend String operator+(null, const String &string);
        friend String operator+(const sByte *bytes, const String &string);
        friend String operator+(const sChar *chars, const String &string);
        friend String operator+(const Object &object, const String &string);
        friend String operator+(const Pointer<Object> &pointer, const String &string);

        String &operator=(null);
        String &operator=(const sByte *bytes);
        String &operator=(const sChar *chars);
        String &operator=(const String &string);
        String &operator=(String &&string);

        String &operator+=(const sInt value);
        String &operator+=(const uInt value);
        String &operator+=(const sByte value);
        String &operator+=(const uByte value);
        String &operator+=(const sLong value);
        String &operator+=(const uLong value);
        String &operator+=(const float value);
        String &operator+=(const double value);
        String &operator+=(const sShort value);
        String &operator+=(const uShort value);

        String &operator+=(null);
        String &operator+=(const sByte *bytes);
        String &operator+=(const sChar *chars);
        String &operator+=(const String &string);
        String &operator+=(const Object &object);
        String &operator+=(const Pointer<Object> &pointer);

        bool operator==(null) const;
        bool operator==(const sByte *bytes) const;
        bool operator==(const sChar *chars) const;
        bool operator==(const String &string) const;
        bool operator==(const Object &object) const override;
        friend bool operator==(null, const String &string);
        friend bool operator==(const sByte *bytes, const String &string);
        friend bool operator==(const sChar *chars, const String &string);

        bool operator!=(null) const;
        bool operator!=(const sByte *bytes) const;
        bool operator!=(const sChar *chars) const;
        bool operator!=(const String &string) const;
        bool operator!=(const Object &object) const override;
        friend bool operator!=(null, const String &string);
        friend bool operator!=(const sByte *bytes, const String &string);
        friend bool operator!=(const sChar *chars, const String &string);

    public:
        sChar &operator[](const heap index);
        const sChar &operator[](const heap index) const;
        const sChar *source() const;
        heap length() const;

        sChar charAt(const heap index = 0) const;
        sChar charCodeAt(const heap index = 0) const;
        // TODO: String concat(... args) const;
        sInt indexOf(const String &string, const heap startIndex = 0) const;
        sInt lastIndexOf(const String &string, const heap startIndex = 0) const;
        // TODO: sInt localeCompare(const String &string, ... args) const;
        // TODO: Array match(const RegExp &pattern) const;
        // TODO: String replace(const RegExp &pattern, const String &replace) const;
        // TODO: sInt search(const RegExp &pattern) const;
        String slice(const heap startIndex = 0, const heap endIndex = 0) const;
        // TODO: Array split(const String &delimiter, const heap limit = Integer::MAX_VALUE) const;
        String substr(const heap startIndex = 0, const heap length = 0) const;
        String substring(const heap startIndex = 0, const heap endIndex = 0) const;
        String toLocaleLowerCase() const;
        String toLocaleString() const override;
        String toLocaleUpperCase() const;
        String toLowerCase() const;
        String toString() const override;
        String toUpperCase() const;
        // TODO: Object valueOf() const override;

    private:
        template<class T, class U> static String concat(const T *lhsBytes, heap lhsLength, const U *rhsBytes, heap rhsLength);
        template<class T> void create(const T *bytes, const heap length);
        template<class T> void append(const T *bytes, const heap length);
        void release();
};

#endif
