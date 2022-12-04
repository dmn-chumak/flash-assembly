#ifndef FLASH_CORE_UTILS_H
#define FLASH_CORE_UTILS_H

#include <flash/core/Type.h>

class Utils final {
    public:
        template<class SrcType>
        static inline SrcType &&move(SrcType &source) {
            return (SrcType &&)source;
        }

        template<class SrcType, class DstType>
        static inline void copy(SrcType *srcFirst, SrcType *srcLast, DstType *dstFirst) {
            while (srcFirst != srcLast) {
                *(dstFirst++) = *(srcFirst++);
            }
        }

        template<class SrcType, class DstType>
        static inline void copyReverse(SrcType *srcFirst, SrcType *srcLast, DstType *dstFirst) {
            while (srcFirst != srcLast) {
                *(dstFirst++) = *(--srcLast);
            }
        }

        template<class SrcType, class DstType>
        static inline void move(SrcType *srcFirst, SrcType *srcLast, DstType *dstFirst) {
            while (srcFirst != srcLast) {
                *(dstFirst++) = Utils::move(*(srcFirst++));
            }
        }

        template<class SrcType, class DstType>
        static inline bool equals(SrcType *srcFirst, SrcType *srcLast, DstType *dstFirst) {
            while (srcFirst != srcLast) {
                if (*(srcFirst++) != *(dstFirst++)) {
                    return false;
                }
            }

            return *srcFirst == *dstFirst;
        }

        template<class SrcType, class DstType>
        static inline bool equals(SrcType *srcFirst, DstType *dstFirst) {
            const SrcType *tmpType = dynamic_cast<SrcType *>(dstFirst);

            if (srcFirst == tmpType) {
                return true;
            }

            if (srcFirst == nullptr
            ||  tmpType == nullptr) {
                return false;
            }

            return *srcFirst == *tmpType;
        }

        template<class SrcType>
        static inline heap length(SrcType *srcFirst) {
            if (srcFirst != nullptr) {
                SrcType *srcLast = srcFirst;
                while (*srcLast != '\0') { srcLast++; }
                return (heap)(srcLast - srcFirst);
            }

            return 0;
        }

        template<class SrcType>
        static inline void reverse(SrcType *srcFirst, SrcType *srcLast) {
            SrcType temp;

            while (srcFirst < srcLast) {
                temp = *srcFirst;
                *(srcFirst++) = *srcLast;
                *(srcLast--) = temp;
            }
        }
};

#endif
