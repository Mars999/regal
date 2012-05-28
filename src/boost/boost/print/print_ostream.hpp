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

#ifndef BOOST_PRINT_OSTREAM_HPP
#define BOOST_PRINT_OSTREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>
#include <boost/print/print_string.hpp>

#include <ostream>

// specialized print to std::ostream

namespace boost { namespace print {

inline size_t print(std::ostream &output)
{
  return 0;
}

template<typename A1>
size_t print(std::ostream &output, const A1 &a1)
{
  std::string tmp;
  print(tmp,a1);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2)
{
  std::string tmp;
  print(tmp,a1,a2);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3)
{
  std::string tmp;
  print(tmp,a1,a2,a3);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9);
  output << tmp;
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
size_t print(std::ostream &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  output << tmp;
  return tmp.length();
}

}}

#endif
