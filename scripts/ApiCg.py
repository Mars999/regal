#!/usr/bin/python

# Cg related API Utility functions

import re

copyrightMessage = '''/*
 *
 * Copyright (c) 2002-2012, NVIDIA Corporation.
 *
 *
 *
 * NVIDIA Corporation("NVIDIA") supplies this software to you in consideration
 * of your agreement to the following terms, and your use, installation,
 * modification or redistribution of this NVIDIA software constitutes
 * acceptance of these terms.  If you do not agree with these terms, please do
 * not use, install, modify or redistribute this NVIDIA software.
 *
 *
 *
 * In consideration of your agreement to abide by the following terms, and
 * subject to these terms, NVIDIA grants you a personal, non-exclusive license,
 * under NVIDIA's copyrights in this original NVIDIA software (the "NVIDIA
 * Software"), to use, reproduce, modify and redistribute the NVIDIA
 * Software, with or without modifications, in source and/or binary forms;
 * provided that if you redistribute the NVIDIA Software, you must retain the
 * copyright notice of NVIDIA, this notice and the following text and
 * disclaimers in all such redistributions of the NVIDIA Software. Neither the
 * name, trademarks, service marks nor logos of NVIDIA Corporation may be used
 * to endorse or promote products derived from the NVIDIA Software without
 * specific prior written permission from NVIDIA.  Except as expressly stated
 * in this notice, no other rights or licenses express or implied, are granted
 * by NVIDIA herein, including but not limited to any patent rights that may be
 * infringed by your derivative works or by other works in which the NVIDIA
 * Software may be incorporated. No hardware is licensed hereunder.
 *
 *
 *
 * THE NVIDIA SOFTWARE IS BEING PROVIDED ON AN "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION, WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR ITS USE AND OPERATION
 * EITHER ALONE OR IN COMBINATION WITH OTHER PRODUCTS.
 *
 *
 *
 * IN NO EVENT SHALL NVIDIA BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL,
 * EXEMPLARY, CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, LOST
 * PROFITS; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) OR ARISING IN ANY WAY OUT OF THE USE,
 * REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION OF THE NVIDIA SOFTWARE,
 * HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT (INCLUDING
 * NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF NVIDIA HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
'''

#
# Sort Cg type enumerants according to base-type (CG_BOOL, CG_FLOAT, etc)
# for tidy-looking headers, rather than enumerant value.
#

typeNameCompareRe = re.compile('^(CG_[A-Z]+)(_TYPE|_STRUCT|_START_ENUM|[1-4]|[1-4]x[1-4]|[1-4]D|[1-4]DARRAY)?$')

def typeNameCompare(i,j):
  if i==j:
    return 0

  # Manually order the non-numerical types first

  if i=='CG_UNKNOWN_TYPE':    return -1
  if j=='CG_UNKNOWN_TYPE':    return  1
  if i=='CG_ARRAY':           return -1
  if j=='CG_ARRAY':           return  1
  if i=='CG_STRING':          return -1
  if j=='CG_STRING':          return  1
  if i=='CG_STRUCT':          return -1
  if j=='CG_STRUCT':          return  1
  if i=='CG_TYPELESS_STRUCT': return -1
  if j=='CG_TYPELESS_STRUCT': return  1
  if i=='CG_TEXTURE':         return -1
  if j=='CG_TEXTURE':         return  1
  if i=='CG_BUFFER':          return -1
  if j=='CG_BUFFER':          return  1
  if i=='CG_UNIFORMBUFFER':   return -1
  if j=='CG_UNIFORMBUFFER':   return  1
  if i=='CG_POINTER':         return -1
  if j=='CG_POINTER':         return  1
  if i=='CG_ADDRESS':         return -1
  if j=='CG_ADDRESS':         return  1

  if i.endswith('_TYPE') and j.endswith('_TYPE'):
    return cmp(i,j)

  if i.endswith('_TYPE'):        return -1
  if j.endswith('_TYPE'):        return  1

  if i.startswith('CG_SAMPLER') and j.startswith('CG_SAMPLER'):
    return cmp(i,j)

  if i.startswith('CG_SAMPLER'): return -1
  if j.startswith('CG_SAMPLER'): return  1

  if i=='CG_TYPE_START_ENUM':    return -1
  if j=='CG_TYPE_START_ENUM':    return  1

  #

  m = typeNameCompareRe.match(i)
  n = typeNameCompareRe.match(j)
  if m and n:
    if m.group(1)==n.group(1):

      s = m.group(2)
      t = n.group(2)
      if s is None:
        s = ''
      if t is None:
        t = ''

      if len(s)==len(t):
        return cmp(s,t)
      else:
        return cmp(len(s),len(t))
    else:
      return cmp(m.group(1),n.group(1))
  else:
    cmp(i,j)  # throw?
