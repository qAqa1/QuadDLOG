#include "TonelliShanks.h"

// https://rosettacode.org/wiki/Tonelli-Shanks_algorithm

using namespace boost::multiprecision;

roots TonelliShanks(cpp_int n, cpp_int p)
{
    cpp_int q = p - 1;
    cpp_int ss = 0;
    cpp_int z = 2;
    cpp_int c, r, t, m;

    if (powm(n, (p - 1) / 2, p) != 1) { return std::nullopt; }

    while ((q & 1) == 0)
    {
        ss += 1;
        q >>= 1;
    }

    if (ss == 1)
    {
        cpp_int r1 = powm(n, (p + 1) / 4, p);
        return MAKE_ROOT(r1, p - r1);
    }

    while (powm(z, (p - 1) / 2, p) != p - 1) z++;

    c = powm(z, q, p);
    r = powm(n, (q + 1) / 2, p);
    t = powm(n, q, p);
    m = ss;

    while (true)
    {
        cpp_int i = 0, zz = t;
        cpp_int b = c, e;

        if (t == 1) { return MAKE_ROOT(r, p - r); }

        while (zz != 1 && i < (m - 1))
        {
            zz = zz * zz % p;
            i++;
        }

        e = m - i - 1;

        while (e > 0)
        {
            b = b * b % p;
            e--;
        }

        r = r * b % p;
        c = b * b % p;
        t = t * c % p;
        m = i;
    }
}
