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

#ifndef BOOST_PRINT_CHAR_VECTOR_HPP
#define BOOST_PRINT_CHAR_VECTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>

#include <vector>   // std::vector<char>

namespace boost { namespace print {

// print_char_vector

template<typename A1>
std::vector<char> print_char_vector(const A1 &a1)
{
  return print_cast< std::vector<char> >(a1);
}

template<typename A1, typename A2>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2)
{
  return print_cast< std::vector<char> >(a1,a2);
}

template<typename A1, typename A2, typename A3>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3)
{
  return print_cast< std::vector<char> >(a1,a2,a3);
}

template<typename A1, typename A2, typename A3, typename A4>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5,a6);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5,a6,a7);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5,a6,a7,a8);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5,a6,a7,a8,a9);
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
std::vector<char> print_char_vector(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  return print_cast< std::vector<char> >(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
}

}}
#endif
