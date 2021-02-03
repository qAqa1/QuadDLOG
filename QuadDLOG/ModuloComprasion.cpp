#include "ModuloComprasion.h"
#include "TonelliShanks.h"

roots ModuloComprasion(boost::multiprecision::cpp_int n, boost::multiprecision::cpp_int p)
{
    return TonelliShanks(n, p);
}
