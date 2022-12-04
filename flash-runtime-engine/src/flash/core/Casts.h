#ifndef FLASH_CORE_CASTS_H
#define FLASH_CORE_CASTS_H

#include <flash/core/String.h>
#include <flash/core/Pointer.h>
#include <flash/core/Utils.h>
#include <flash/runtime/Number.h>
#include <flash/utils/Math.h>

class Casts final {
    public:
        template<class Type>
        static sChar *itos(Type source, uInt radix, sChar *result, uInt &length) {
            if (radix < 2 || radix > 36) {
                radix = 10;
            }

            //-------------------------

            if (result == nullptr) {
                result = new sChar[sizeof(Type) * 2 + 4];
            }

            //-------------------------

            Type value = (source > 0) ? source : -source;
            Type chunk;

            //-------------------------

            do {
                chunk  = value % radix;
                value /= radix;

                result[length++] = static_cast<sChar>(
                      (chunk >= 0xA)
                    ? ('A' + chunk - 0xA)
                    : ('0' + chunk)
                );
            } while (value > 0);

            //-------------------------

            if (source < 0) {
                result[length++] = '-';
            }

            //-------------------------

            Utils::reverse(
                result,
                result + length - 1
            );

            //-------------------------

            return result;
        }

        template<class Type>
        static String itos(Type source, uInt radix, uInt zeros) {
            uInt digits = sizeof(Type) * 2 + 4;
            RawArrPtr<sChar> result = new sChar[zeros > digits ? zeros : digits];
            uInt length = 0;

            //-------------------------

            Casts::itos(
                source,
                radix,
                result.get(),
                length
            );

            //-------------------------

            if (zeros > length) {
                uInt offset = zeros - length;

                for (uInt index = 0; index < length; ++index) {
                    result[zeros - index - 1] = result[length - index - 1];
                }

                for (uInt index = 0; index < offset; ++index) {
                    result[index] = '0';
                }

                length = zeros;
            }

            //-------------------------

            return String(
                result.get(),
                length
            );
        }

        template<class Type>
        static String itos(Type source, uInt radix = 10) {
            RawArrPtr<sChar> result = new sChar[sizeof(Type) * 2 + 4];
            uInt length = 0;

            //-------------------------

            Casts::itos(
                source,
                radix,
                result.get(),
                length
            );

            //-------------------------

            return String(
                result.get(),
                length
            );
        }

        template<class Type>
        static String ftos(Type source, uInt precision = 100, bool complete = false, bool exponent = false) {
            if (precision > 100) {
                precision = 100;
            }

            //-------------------------

            // [ 100 = precision, 5 = exponent ]
            RawArrPtr<sChar> result = new sChar[105];
            sInt integerPart = flash::runtime::Number::castFloat64(source);
            Type floatingPart = source - integerPart;
            uInt length = 0;

            //-------------------------

            if (integerPart < 0) {
                integerPart = -integerPart;
            }

            if (floatingPart < 0) {
                floatingPart = -floatingPart;
            }

            if (source < 0) {
                result[length++] = '-';
            }

            //-------------------------

            Casts::itos(
                integerPart,
                10,
                result.get() + length,
                length
            );

            //-------------------------

            if (precision != 0 && (floatingPart > 0 || complete)) {
                result[length++] = '.';

                while (precision-- > 0 && (floatingPart > 0 || complete)) {
                    floatingPart *= 10;
                    integerPart = flash::runtime::Number::castFloat64(floatingPart);
                    result[length++] = static_cast<sChar>('0' + integerPart);
                    floatingPart -= integerPart;
                }
            }

            //-------------------------

            return String(
                result.get(),
                length
            );
        }
};

#endif
