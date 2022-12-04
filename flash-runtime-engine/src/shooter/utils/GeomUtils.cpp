#include <shooter/utils/GeomUtils.h>

namespace shooter::utils {
    void GeomUtils::concat(Pointer<Matrix> base, Pointer<Matrix> from, Pointer<Matrix> prep) {
        base->setTo(
            from->a * prep->a + from->c * prep->b, from->b * prep->a + from->d * prep->b,
            from->a * prep->c + from->c * prep->d, from->b * prep->c + from->d * prep->d,
            from->tx + from->a * prep->tx + from->c * prep->ty,
            from->ty + from->b * prep->tx + from->d * prep->ty
        );
    }

    bool GeomUtils::identity(Pointer<Matrix> matrix) {
        return (
            matrix->a == Double(1) &&
            matrix->b == Double(0) &&
            matrix->c == Double(0) &&
            matrix->d == Double(1) &&
            matrix->tx == Double(0) &&
            matrix->ty == Double(0)
        );
    }

}

