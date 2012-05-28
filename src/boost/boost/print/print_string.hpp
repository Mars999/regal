/*
 * Copyright (c) 2010-2012 NVIDIA Corporation
 * Copyright (c) 2010-2012 Nigel Stewart
 * All rights reserved.
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * boost::print is a library for string conversion.
 * boost::print is not currently a part of boost.
 */

#ifndef BOOST_PRINT_STRING_HPP
#define BOOST_PRINT_STRING_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>

#include <string>

// boost::print::print_string is boost::print::print_cast<std::string>

namespace boost { namespace print {

inline
std::string print_string()
{
  return print_cast<std::string>();
}

template<typename A1>
std::string print_string(const A1 &a1)
{
  return print_cast<std::string>(a1);
}

template<typename A1, typename A2>
std::string print_string(const A1 &a1, const A2 &a2)
{
  return print_cast<std::string>(a1,a2);
}

template<typename A1, typename A2, typename A3>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3)
{
  return print_cast<std::string>(a1,a2,a3);
}

template<typename A1, typename A2, typename A3, typename A4>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  return print_cast<std::string>(a1,a2,a3,a4);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20>
std::string print_string(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19, const A20 &a20)
{
  return print_cast<std::string>(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
}

}}

#endif
