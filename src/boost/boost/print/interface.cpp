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

#include "interface.hpp"

namespace boost { namespace print { namespace extend {

std::size_t length(const ::boost::print::detail::array<boost::uint8_t, const char *> &val)
{
  return ::boost::print::extend::length<boost::uint8_t, const char *>(val);
}

std::size_t length(const ::boost::print::detail::array<boost::uint16_t, const char *> &val)
{
  return length<boost::uint16_t, const char *>(val);
}

std::size_t length(const ::boost::print::detail::array<boost::uint32_t, const char *> &val)
{
  return length<boost::uint32_t, const char *>(val);
}

std::size_t length(const ::boost::print::detail::array<boost::uint64_t, const char *> &val)
{
  return length<boost::uint64_t, const char *>(val);
}

std::size_t length(const ::boost::print::detail::array<float, const char *> &val)
{
  return length<float, const char *>(val);
}

std::size_t length(const ::boost::print::detail::array<double, const char *> &val)
{
  return length<double, const char *>(val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<boost::uint8_t, const char *> &val)
{
  write<std::string::iterator,boost::uint8_t,const char *>(i,val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<boost::uint16_t, const char *> &val)
{
  write<std::string::iterator,boost::uint16_t,const char *>(i,val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<boost::uint32_t, const char *> &val)
{
  write<std::string::iterator,boost::uint32_t,const char *>(i,val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<boost::uint64_t, const char *> &val)
{
  write<std::string::iterator,boost::uint64_t,const char *>(i,val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<float, const char *> &val)
{
  write<std::string::iterator,float,const char *>(i,val);
}

void write(std::string::iterator &i, const ::boost::print::detail::array<double, const char *> &val)
{
  write<std::string::iterator,double,const char *>(i,val);
}

}}}
