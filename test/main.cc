#define D_AKR_TEST
#include "akr_test.hh"

#include "../range.hh"

#include <chrono>
#include <cstdio>

int main()
{
    for (auto i : akr::Range(0, 10))
    {
        std::printf("%2d ", i);
    }
    puts("");

    for (auto i : akr::Range(0, 10,  2))
    {
        std::printf("%2d ", i);
    }
    puts("");

    for (auto i : akr::Range(10, 0, -1))
    {
        std::printf("%2d ", i);
    }
    puts("");

    for (auto i : akr::Range(10, 0, -2))
    {
        std::printf("%2d ", i);
    }
    puts("");
}
