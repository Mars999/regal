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

#ifndef BOOST_PRINT_CORE_HPP
#define BOOST_PRINT_CORE_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/detail.hpp>
#include <boost/print/interface.hpp>

//
// boost::print namespace for public API - print, print_cast
//

namespace boost { namespace print {

// Generic print

template<typename T>
size_t print(T &output)
{
  output.clear();
  return 0;
}

template<typename A1, typename T>
size_t print(T &output, const A1 &a1)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
  assert(i==output.end());
  return size;
}

template<typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20, typename T>
size_t print(T &output, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19, const A20 &a20)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);

  output.clear();
  output.resize(size,' ');

  typename T::iterator i = output.begin();
  write(i,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
  assert(i==output.end());
  return size;
}

// print_buffer

template<typename T>
size_t print_buffer(T *output, const size_t n)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  if (output)
  {
    if (n>0)    *output = '\0';
  }
  return 0;
}

template<typename T, typename A1>
size_t print_buffer(T *output, const size_t n, const A1 &a1)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1);
  if (output)
  {
    if (n>size) write(output,a1);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2);
  if (output)
  {
    if (n>size) write(output,a1,a2);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20>
size_t print_buffer(T *output, const size_t n, const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19, const A20 &a20)
{
  using boost::print::extend::length;
  using boost::print::extend::write;

  const ::std::size_t size = length(a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
  if (output)
  {
    if (n>size) write(output,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
    if (n>0)    *output = '\0';
  }
  return size;
}

template<typename Iterator, typename A1>
size_t print_iterator(Iterator begin, Iterator end, const A1 &a1) { return print_buffer(begin,static_cast<size_t>(end-begin),a1); }

//

template<typename T>
inline T print_cast()
{
  return T();
}

template<typename T, typename A1>
T print_cast(const A1 &a1)
{
  T tmp;
  print(tmp,a1);
  return tmp;
}

template<typename T, typename A1, typename A2>
T print_cast(const A1 &a1, const A2 &a2)
{
  T tmp;
  print(tmp,a1,a2);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3)
{
  T tmp;
  print(tmp,a1,a2,a3);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4)
{
  T tmp;
  print(tmp,a1,a2,a3,a4);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19);
  return tmp;
}

template<typename T, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19, typename A20>
T print_cast(const A1 &a1, const A2 &a2, const A3 &a3, const A4 &a4, const A5 &a5, const A6 &a6, const A7 &a7, const A8 &a8, const A9 &a9, const A10 &a10, const A11 &a11, const A12 &a12, const A13 &a13, const A14 &a14, const A15 &a15, const A16 &a16, const A17 &a17, const A18 &a18, const A19 &a19, const A20 &a20)
{
  T tmp;
  print(tmp,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15,a16,a17,a18,a19,a20);
  return tmp;
}

}}

#endif
