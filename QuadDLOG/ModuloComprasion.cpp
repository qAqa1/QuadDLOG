#include "ModuloComprasion.h"
#include "TonelliShanks.h"
#include "CantorZassenhaus.h"

roots ModuloComprasion(int n, boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int p)
{
    if (n == 2) return TonelliShanks(a, p);
    auto rts = CantorModularComprassion(n, a, p);
    return rts.empty() ? std::nullopt : std::make_optional(CantorModularComprassion(n, a, p));
}
