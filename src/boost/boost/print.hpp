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
 *
 * Design Goals:
 *   - Support std::string, char * and std::vector<char> and other forms of string output
 *   - Efficient in time and space
 *   - No dependency on printf or C++ iostreams
 *   - Minimal dependencies except for std::string, std::strlen, std::malloc, std::vector
 *   - Can be used with or without the rest of boost
 *   - Extensible to other data types, structs and containers
 *   - Support for user-defined types and custom formatting
 *
 * Features:
 *   - Three step algorithm: determine the string length, allocate, and print
 *   - Supports integer, float and string inputs
 *   - Support for binary (0 or 1), octal and hexadecimal formatting of integers.
 *
 * Limitations:
 *   - No direct fprint output
 *   - No direct ostream output
 *   - No locale support by design (it could be added as an option, we don't want it)
 *   - No float or double support yet (it could be added, we don't need it)
 *   - No support for octal output yet (it could be added, we don't need it)
 *
 * Testing:
 *   - Compiles and runs for OSX Leopard ppc, i386 and x86_64 architectures. (gcc 4.0.1)
 *   - Compiles and runs for Linux x86 and x86_64 arhitectures. (gcc 4.1.2)
 *   - Compiles and runs for Solaris x86 and x86_64 architectures. (SunStudio 12)
 *   - Compiles and runs for Windows VC7, VC8, VC9, VC10. x86 and x86_64 architectures.
 *
 * Examples:

  // Print to std::string

  std::string string;
  boost::print::print(string,"Hello",' ',"World",'!');
  std::cout << string << std::endl;

  // Print to std::wstring

  std::wstring wstring;
  boost::print::print(wstring,"Hello"," Wide ","World",'!');

  // Print to std::vector<char>, etc

  std::vector<char> char_vector;
  boost::print::print(char_vector,"Hello"," Vector",'?');

  std::vector<int> int_vector;
  boost::print::print(int_vector,"Hello"," Vector "," of int.");

  // Print to char buffer with unknown length

  char buffer[1024];
  boost::print::print(buffer,"This might exceed the buffer size.");
  std::cout << buffer << std::endl;

  // Print to char buffer with specified length

  boost::print::print_buffer(buffer,sizeof(buffer),"This won't overwrite the buffer.");
  std::cout << buffer << std::endl;

  // Print to char buffer with specified begin and end iterators

  boost::print::print_iterator(buffer,buffer+sizeof(buffer),"Iterators can be used for safety too");
  std::cout << buffer << std::endl;

  // Print to FILE * or std::ostream

  boost::print::print(stdout, "Works the same for FILE * ...",'\n');
  boost::print::print(std::cout, "... and std::ostream too.",'\n');

  // Print to std::string

  std::cout << boost::print::print_string("1+1 = ",1+1) << std::endl;

  // Print to dynamically allocated char buffer

  char *message = boost::print::print_c_str("Don't forget to free() the message when you're done with it.");
  std::printf("%s\n",message);
  std::free(message);

*/

#ifndef BOOST_PRINT_HPP
#define BOOST_PRINT_HPP

#if defined(_MSC_VER) && (_MSC_VER>=1200)
#pragma once
#endif

#include <boost/print/core.hpp>
#include <boost/print/print_string.hpp>
#include <boost/print/print_c_str.hpp>
#include <boost/print/print_char_vector.hpp>
#include <boost/print/print_file.hpp>
#include <boost/print/print_ostream.hpp>
#include <boost/print/printf.hpp>

#endif
