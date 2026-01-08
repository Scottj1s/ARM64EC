// LibNonEC.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include <string>

std::wstring AppendStrings(std::wstring const& s1, std::wstring const& s2)
{
    std::wstring s(s1);
    s.append(s2);
    return s;
}
