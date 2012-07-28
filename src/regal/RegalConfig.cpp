/*
  Copyright (c) 2011-2012 NVIDIA Corporation
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

namespace Config {

bool forceCoreProfile = false;
bool forceEmulation   = REGAL_FORCE_EMULATION;
bool enableEmulation  = true;
bool enableDebug      = false;
bool enableError      = false;
bool enableEmuPpa     = REGAL_EMU_PPA;
bool enableEmuObj     = REGAL_EMU_OBJ;
bool enableEmuBin     = REGAL_EMU_BIN;
bool enableEmuDsa     = REGAL_EMU_DSA;
bool enableEmuIff     = REGAL_EMU_IFF;
bool enableEmuVao     = REGAL_EMU_VAO;

void Init()
{
  ITrace("Config::Init");

#ifndef REGAL_NO_GETENV
  const char *tmp;

  tmp = GetEnv( "REGAL_FORCE_CORE_PROFILE" );
  if (tmp) forceCoreProfile = atoi(tmp)!=0;

#if !REGAL_FORCE_EMULATION
  tmp = GetEnv( "REGAL_FORCE_EMULATION" );
  if (tmp) forceEmulation = atoi(tmp)!=0;
#endif

  tmp = GetEnv( "REGAL_NO_EMULATION" );
  if (tmp) enableEmulation = atoi(tmp)==0;

  tmp = GetEnv( "REGAL_DEBUG" );
  if (tmp) enableDebug = atoi(tmp)!=0;

  tmp = GetEnv( "REGAL_ERROR" );
  if (tmp) enableError = atoi(tmp)!=0;

#if REGAL_EMU_PPA
  tmp = GetEnv( "REGAL_EMU_PPA" );
  if (tmp) enableEmuObj = atoi(tmp)!=0;
#endif

#if REGAL_EMU_OBJ
  tmp = GetEnv( "REGAL_EMU_OBJ" );
  if (tmp) enableEmuObj = atoi(tmp)!=0;
#endif

#if REGAL_EMU_BIN
  tmp = GetEnv( "REGAL_EMU_BIN" );
  if (tmp) enableEmuBin = atoi(tmp)!=0;
#endif

#if REGAL_EMU_DSA
  tmp = GetEnv( "REGAL_EMU_DSA" );
  if (tmp) enableEmuDsa = atoi(tmp)!=0;
#endif

#if REGAL_EMU_IFF
  tmp = GetEnv( "REGAL_EMU_IFF" );
  if (tmp) enableEmuIff = atoi(tmp)!=0;
#endif

#if REGAL_EMU_VAO
  tmp = GetEnv( "REGAL_EMU_VAO" );
  if (tmp) enableEmuVao = atoi(tmp)!=0;
#endif
#endif

#ifdef REGAL_FORCE_CORE_PROFILE
  forceCoreProfile = (REGAL_FORCE_CORE_PROFILE) != 0;
#endif

#ifdef REGAL_NO_EMULATION
  enableEmulation = (REGAL_NO_EMULATION) == 0;
#endif

#ifdef REGAL_DEBUG
  enableDebug = (REGAL_DEBUG) != 0;
#endif

#ifdef REGAL_ERROR
  enableDebug = (REGAL_ERROR) != 0;
#endif

  Info("REGAL_FORCE_CORE_PROFILE ", forceCoreProfile ? "enabled" : "disabled");
  Info("REGAL_FORCE_EMULATION    ", forceEmulation   ? "enabled" : "disabled");
  Info("REGAL_NO_EMULATION       ", !enableEmulation ? "enabled" : "disabled");
  Info("REGAL_DEBUG              ", enableDebug      ? "enabled" : "disabled");
  Info("REGAL_ERROR              ", enableError      ? "enabled" : "disabled");

  Info("REGAL_EMU_PPA            ", enableEmuPpa     ? "enabled" : "disabled");
  Info("REGAL_EMU_OBJ            ", enableEmuObj     ? "enabled" : "disabled");
  Info("REGAL_EMU_BIN            ", enableEmuBin     ? "enabled" : "disabled");
  Info("REGAL_EMU_DSA            ", enableEmuDsa     ? "enabled" : "disabled");
  Info("REGAL_EMU_IFF            ", enableEmuIff     ? "enabled" : "disabled");
  Info("REGAL_EMU_VAO            ", enableEmuVao     ? "enabled" : "disabled");
}

}

REGAL_NAMESPACE_END
