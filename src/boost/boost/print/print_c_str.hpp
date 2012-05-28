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

#ifndef BOOST_PRINT_PRINT_C_STR_HPP
#define BOOST_PRINT_PRINT_C_STR_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>

#include <cstdlib>  // malloc
#include <cstddef>  // diffptr_t
#include <cassert>  // assert

namespace boost { namespace print {

// specialized print to char * or wchar *

template<typename T>
size_t print(T *output)
{
  if (output) output[0] = '\0';
  return 0;
}

template<typename T, typename A1>
size_t print(T *output, const A1 &a1)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1);
  if (output)
  {
    T *i = output;
    write(i,a1);
    assert(i-output==static_cast<std::ptrdiff_t>(len));
    output[0] = '\0';
  }
  return len;
}

template<typename T, typename A1, typename A2>
size_t print(char *output, const A1 &a1, const A2 &a2)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2);
  if (output)
  {
    T *i = output;
    write(i,a1,a2);
    assert(i-output==static_cast<std::ptrdiff_t>(len));
    output[0] = '\0';
  }
  return len;
}

template<typename T, typename A1, typename A2, typename A3>
size_t print(char *output, const A1 &a1, const A2 &a2, const A3 &a3)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3);
  if (output)
  {
    T *i = output;
    write(i,a1,a2,a3);
    assert(i-output==static_cast<std::ptrdiff_t>(len));
    output[0] = '\0';
  }
  return len;
}

template<typename T, typename A1, typename A2, typename A3, typename A4>
size_t print(char *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4);
  if (output)
  {
    T *i = output;
    write(i,a1,a2,a3,a4);
    assert(i-output==static_cast<std::ptrdiff_t>(len));
    output[0] = '\0';
  }
  return len;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
size_t print(char *output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5);
  if (output)
  {
    T *i = output;
    write(output,a1,a2,a3,a4,a5);
    assert(i-output==static_cast<std::ptrdiff_t>(len));
    output[0] = '\0';
  }
  return len;
}

// boost::print::print_c_str

inline char *print_c_str()
{
  char *tmp = (char *) std::malloc(1);
  *tmp = '\0';
  return tmp;
}

template<typename A1>
char *print_c_str(const A1 &a1)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2>
char *print_c_str(const A1 &a1, const A2 &a2)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5,a6);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5,a6);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5,a6,a7);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5,a6,a7);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5,a6,a7,a8);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5,a6,a7,a8);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5,a6,a7,a8,a9);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
char *print_c_str(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const std::size_t len = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  char *tmp = (char *) std::malloc(len+1);
  char *i = tmp;
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  assert(i-tmp==static_cast<std::ptrdiff_t>(len));
  *i = '\0';
  return tmp;
}

}}

#endif
