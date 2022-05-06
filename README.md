# **akr::Range**

## **Contents**

  - [1. Require](#1-require)
  - [2. Usage](#2-usage)

## **1. Require**
* ### `C++20`

## **2. Usage**
```c++
#include "range.hh"

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
```
