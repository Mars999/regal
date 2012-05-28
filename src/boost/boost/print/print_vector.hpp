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

#include <boost/print.hpp>

#include <vector>   // std::vector<char>

namespace boost { namespace print {

// print_char_vector

template<typename A1>
std::vector<char> print_char_vector(A1 a1)
{
  return print_cast< std::vector<char> >(a1);
}

}}
#endif
