#include <flash/utils/Endian.h>

namespace flash::utils {
    const sByte *Endian::BIG_ENDIAN     = "bigEndian";
    const sByte *Endian::LITTLE_ENDIAN  = "littleEndian";
    const sByte *Endian::CURRENT        = LITTLE_ENDIAN;
}
