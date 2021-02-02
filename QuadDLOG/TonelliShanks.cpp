#include "TonelliShanks.h"

// https://rosettacode.org/wiki/Tonelli-Shanks_algorithm

//#include <iostream>


//#include <optional>
//#include <utility>
//#include <algorithm>

using namespace boost::multiprecision;

//struct Solution
//{
//    cpp_int root1, root2;
//    bool exists;
//};
//
//struct Solution makeSolution(cpp_int root1, cpp_int root2, bool exists)
//{
//    struct Solution sol;
//    sol.root1 = root1;
//    sol.root2 = root2;
//    sol.exists = exists;
//    return sol;
//}

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
        //return makeSolution(r1, p - r1, true);
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

        //if (t == 1) { return makeSolution(r, p - r, true); }
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