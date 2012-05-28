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

#ifndef BOOST_PRINT_FILE_HPP
#define BOOST_PRINT_FILE_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>

#include <cstdio>

// specialized print to FILE *

namespace boost { namespace print {

inline ::std::size_t print(std::FILE *output)
{
  return 0;
}

template<typename A1>
::std::size_t print(std::FILE *output, const A1 &a1)
{
  ::std::string tmp;
  print(tmp,a1);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2)
{
  ::std::string tmp;
  print(tmp,a1,a2);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
::std::size_t print(std::FILE *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12)
{
  ::std::string tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
  ::std::fprintf(output,"%s",tmp.c_str());
  return tmp.length();
}

//

}}
#endif
