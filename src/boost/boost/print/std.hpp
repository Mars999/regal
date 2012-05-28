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

#ifndef BOOST_PRINT_STD_HPP
#define BOOST_PRINT_STD_HPP

#include <cstdio>

#include "print_file.hpp"

//
// boost::print::std namespace for ostream emulation via std::FILE
//

namespace boost { namespace print { namespace std {

class ostream
{
public:
  ostream()                     : _file(NULL)        {}
  ostream(::std::FILE *file)    : _file(file)        {}
  ostream(const ostream &other) : _file(other._file) {}

  template<typename T>
  ostream &operator<<(const T &in)
  {
    if (_file)
      boost::print::print(_file,in);
    return *this;
  }

  ostream &flush() { if (_file) ::std::fflush(_file); return *this; }

private:
  ::std::FILE *_file;
};

class ofstream : public ostream
{
public:
  ofstream()                      : ostream()                           {}
  ofstream(const char * filename) : ostream(::std::fopen(filename,"r")) {}
  ofstream(const ofstream &other) : ostream()                           {}
  ~ofstream()                                                           { /* close the file? */ }

  ofstream &close() { return *this; }
};

class strstream
{
public:
  strstream()                 : _str(NULL), _pos(NULL), _end(NULL)  {}
  strstream(char *str, int n) : _str(str),  _pos(str),  _end(str+n) { if (_pos<_end) *_pos = '\0'; }  // Output only
  ~strstream()                                                      {}

  int pcount() const { return int(_pos-_str); }

  char *str()  const { return _str; }

  template<typename T>
  strstream &operator<<(const T &val)
  {
    if (_pos<_end)
    {
      ::std::size_t n = boost::print::print_buffer(_pos, _end-_pos, val);
      if (_pos + n < _end)
        _pos += n;
    }
    return *this;
  }

private:
  char *_str;
  char *_pos;
  char *_end;
};

const char endl = '\n';

} } }

#endif
