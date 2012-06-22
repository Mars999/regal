/*
  Copyright (c) 2011 NVIDIA Corporation
  Copyright (c) 2011-2012 Cass Everitt
  Copyright (c) 2012 Scott Nations
  Copyright (c) 2012 Mathias Schott
  Copyright (c) 2012 Nigel Stewart
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
  OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "pch.h" /* For MS precompiled header support */

#include "RegalUtil.h"

REGAL_GLOBAL_BEGIN

#include <boost/print/print_string.hpp>
using boost::print::print_string;

#include "RegalLog.h"
#include "RegalConfig.h"

REGAL_GLOBAL_END

REGAL_NAMESPACE_BEGIN

Config Config::config;

Config::Config()
: forceCoreProfile(false),
  enableEmulation(true),
  enableDebug(false)
{
#ifndef REGAL_NO_GETENV
  const char *tmp;

  tmp = GetEnv( "REGAL_FORCE_CORE_PROFILE" );
  if (tmp) forceCoreProfile = atoi(tmp)!=0;

  tmp = GetEnv( "REGAL_NO_EMULATION" );
  if (tmp) enableEmulation = atoi(tmp)==0;

  tmp = GetEnv( "REGAL_DEBUG" );
  if (tmp) enableDebug = atoi(tmp)!=0;
#endif

  Info("REGAL_FORCE_CORE_PROFILE ", forceCoreProfile ? "enabled" : "disabled");
  Info("REGAL_NO_EMULATION       ", !enableEmulation ? "enabled" : "disabled");
  Info("REGAL_DEBUG              ", enableDebug      ? "enabled" : "disabled");
}
  
REGAL_NAMESPACE_END
