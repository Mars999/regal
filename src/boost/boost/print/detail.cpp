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

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include "detail.hpp"

//
// boost::print::detail namespace for internal implementation purposes
//

namespace boost { namespace print { namespace detail {

// Determine the number of digits of an unsigned integer
// Use binary search to minimise comparisons.

// 8-bit unsigned integer

size_t unsigned_length(const boost::uint8_t val)
{
  return val<10 ? 1 : (val<100 ? 2 : 3);
}

// 16-bit unsigned integer

size_t unsigned_length(const boost::uint16_t val)
{
  if (val<1000)
    return val<10 ? 1 : (val<100 ? 2 : 3);
  else
    return val<10000 ? 4 : 5;
}

// 32-bit unsigned integer

size_t unsigned_length(const boost::uint32_t val)
{
  if (val<10000)
    return val<100 ? (val<10 ? 1 : 2) : (val<1000 ? 3 : 4);
  else
    return val<10000000 ?
      ( val < 100000 ? 5 : (val<1000000 ? 6 : 7)) :
      ( val < 100000000 ? 8 : (val<1000000000 ? 9 : 10));
}

// 64-bit unsigned integer

size_t unsigned_length(const boost::uint64_t val)
{
  if (val<100000000ll)
  {
    if (val<10000)
      return val<100 ? (val<10 ? 1 : 2) : (val<1000 ? 3 : 4);
    else
      return val<1000000 ? (val<100000 ? 5 : 6) : (val<10000000 ? 7 : 8);
  }
  else
  {
    if (val<1000000000000ll)
      return val<10000000000ll ? (val<1000000000ll ? 9 : 10) : (val<100000000000ll ? 11 : 12);
    else
    {
      if (val<10000000000000000ll)
        return val<100000000000000ll ? (val<10000000000000ll ? 13 : 14) : (val<1000000000000000ll ? 15 : 16);
      else
        return val<1000000000000000000ll ? (val<100000000000000000ll ? 17 : 18) : (val<10000000000000000000ull ? 19 : 20);
    }
  }
}

// Output unsigned integer

void write_unsigned(std::string::iterator &i,  boost::uint8_t val)
{
  return write_unsigned<std::string::iterator, boost::uint8_t>(i,val);
}

void write_unsigned(std::string::iterator &i,  boost::uint16_t val)
{
  return write_unsigned<std::string::iterator, boost::uint16_t>(i,val);
}

void write_unsigned(std::string::iterator &i,  boost::uint32_t val)
{
  return write_unsigned<std::string::iterator, boost::uint32_t>(i,val);
}

void write_unsigned(std::string::iterator &i,  boost::uint64_t val)
{
  return write_unsigned<std::string::iterator, boost::uint64_t>(i,val);
}

}}}
