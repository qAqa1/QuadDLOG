#include "GlobalDefine.h"

#include <functional>

std::string ToString(roots r) { return r ? ToString(r.value()) : "ROOT_NOT_EXIST"; }

void Print(roots r) { std::cout << std::endl << ToString(r); }
