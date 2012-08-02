#!/usr/bin/python

# ApiCodeFilter.py
#
# Routines for filtering source code for output purposes.

import re
import sys

# Expand tab characters into spaces

def expandtabs(code, tabsize = 2):
  tmp = ''
  for i in code.splitlines():
    tmp += i.expandtabs(tabsize) + '\n'
  return ''.join(tmp)

# Trim extraneous trailing whitespace

def trim(code):
  tmp = ''
  for i in code.splitlines():
    tmp += i.rstrip() + '\n'
  return ''.join(tmp)

# Fold repetitive if blocks
#
# if (foo)
#    doo_a();
# if (foo)
#    doo_b();
#
# ->
#
# if (foo)
# {
#    doo_a();
#    doo_b();
# }
#
# NOTE - this logic is only correct for the situation
#        that foo is invariant for the scope of the
#        if blocks.  Perhaps we ought to tighten-up
#        this logic.

def foldIfs(code):
  tmp = code.splitlines()
  i = 0
  while i<len(tmp):
    if tmp[i].strip().startswith('if ('):
      indent = tmp[i].find('if (')
      j = i+2
      while j<len(tmp) and tmp[j]==tmp[i]:
        j = j + 2
      if j>i+2:
        c = [ tmp[i], '%s{'%(' '*indent) ]
        k = i+1
        while k<j:
          c.append(tmp[k])
          k = k + 2
        c.append('%s}'%(' '*indent))
        tmp[i:j] = c
    i = i+1
  return '\n'.join(tmp) + '\n'

# Fold empty #if blocks

def foldPreprocessorIfs(code):
  tmp = code.splitlines()
  i = 0
  while (i+1)<len(tmp):
    if tmp[i].strip().startswith('#if') and tmp[i+1].strip().startswith('#endif'):
      del tmp[i]
      del tmp[i]
      if i>0:
        i = i - 1
    else:
      i = i + 1
  return '\n'.join(tmp) + '\n'

# Fold consecutive empty lines

def foldEmptyLines(code):
  tmp = code.splitlines()
  i = 0
  while (i+1)<len(tmp):
    if len(tmp[i].strip())==0 and len(tmp[i+1].strip())==0:
      del tmp[i+1]
    else:
      i = i + 1
  return '\n'.join(tmp) + '\n'

# Delete break following a return statement

def foldImpossibleBreak(code):
  tmp = code.splitlines()
  i = 0
  while (i+1)<len(tmp):
    if tmp[i].strip().startswith('return') and tmp[i+1].strip()=='break;':
      del tmp[i+1]
    else:
      i = i + 1
  return '\n'.join(tmp) + '\n'

# Delete return following a return statement

def foldImpossibleReturn(code):
  tmp = code.splitlines()
  i = 0
  while (i+1)<len(tmp):
    if tmp[i].strip().startswith('return') and tmp[i+1].strip()=='return;':
      del tmp[i+1]
    else:
      i = i + 1
  return '\n'.join(tmp) + '\n'

# Fold redundant case statements
#
# case a:
# case b:
# case c:
# default:  { ... }
#
# ->
#
# default:  { ... }
#

def foldRedundantCase(code):
  tmp = code.splitlines()
  i = 0
  while (i+1)<len(tmp):
    j = i
    while (j+1)<len(tmp) and tmp[j].strip().startswith('case ') and tmp[j].strip().endswith(':'):
      j = j + 1
    if (j+1)<len(tmp) and tmp[j].strip().startswith('default:'):
      del tmp[i:j]
      i = j + 1
    else:
      i = i + 1
  return '\n'.join(tmp) + '\n'
