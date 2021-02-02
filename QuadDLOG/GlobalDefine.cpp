#include "GlobalDefine.h"

std::string ToString(roots r)
{
	std::stringstream ss;

	if (r)
	{
		ss << "{" << r->first << ", " << r->second << "}";
	}
	else
	{
		ss << "ROOT_NOT_EXIST";
	}

	return ss.str();
}

void Print(roots r) { std::cout << std::endl << ToString(r); }
