#!/usr/bin/python

import os.path
import re
import sys

from ApiType import findType
from ApiType import typesBasic
from ApiType import typeStrip

from ApiCodeGen import typeCode
from ApiCodeGen import paramNameCode

# Code generation for const pointer version of type.

rePtrPtr     = re.compile('(?P<ptrPtr>\*\s*\*)')
reCharPtrPtr = re.compile('^\s*(const)*\s*(char)\s*(const)*\s*\*\s*\*\s*$')
reVoidPtr    = re.compile('^\s*(const)*\s*(void)\s*(const)*\s*\*\s*$')

def typeConstPtrCode(pType):

  const = pType.strip()
  deRef = ''

  if const.find('*') is -1:
    deRef = '*'

  # Special case for char **
  if reCharPtrPtr.match(const):
    const = 'const cgiArgs *'
    deRef = ''

  indConst = const.find('const')
  indPtr   = const.find('*')
  if indConst is -1 or (indPtr is not -1 and indPtr < indConst):
    const = 'const ' + const

  # Convert any '**' to '* const *'.
  while rePtrPtr.search(const):
    const = rePtrPtr.sub('* const *', const)

  const = typeCode(const)

  return const, deRef

# Code generation for using helper function.

reHelper = re.compile('^\s*(?P<name>helper[\w-]+)\s*\((?P<param>.*)\)\s*$')

def helperFuncCode(helper, default = 0):

  if not helper or not len(helper.strip()):
    return ''

  mHelper = reHelper.match(helper)
  if mHelper:
    return '%s ? %s : %s' % (mHelper.group('name'), helper.strip(), default)

  # Warn that helper expression contains 'helper'.
  if helper.find('helper') is not -1:
    print 'Helper function %s not recognized.' % helper
    return None

  return ''

# Code generation translation from <input> to $<input>$.
#   Used by helperTranslateCode.

def helperTranslateMatch(matchObject):

  paramInput = matchObject.group('param')
  if paramInput:
    return matchObject.group(0).replace(paramInput, '$%s$' % paramInput)

  return matchObject.group(0)

# Code generation translation from inputs to outputs.

def helperTranslateCode(helper, inputs, outputs):

  # Check if helper is a string.
  if not helper or not len(helper):
    return helper

  # Check if there are any inputs.
  if not len(inputs):
    return helper

  # Check if num of inputs and outputs is the same.
  if len(inputs) != len(outputs):
    print inputs
    print outputs
    return None

  # Add $ gaurds to inputs.

  code = ' %s ' % helper
  for i in range(len(inputs)):
    # Use following characters to split parameters: [\[\]\(\),\s*+-.].
    regexp = r'[\[(,\s*+-]+(?P<param>%s)+[,)\]\s*+-.]+' % inputs[i]
    code = re.sub(regexp, helperTranslateMatch, code)
  code = code[1:-1]

  # Replace $<input>$ with <output>.

  for i in range(len(inputs)):
    code = code.replace('$%s$' % inputs[i], outputs[i])

  return code

# Code generation for parmeter size format and value.
#
# Example parameter.size specifications:
#   size = 1
#   size = 'n'                                # n is another parameter
#   size = 'count * 2'                        # count is another parameter
#   size = 'helperCgGetArrayDimSize(param)'   # helper function

reConditional = re.compile('^.+\?.+\:.+$')             # a ? b : c
reVariable    = re.compile('^[a-zA-z_][a-zA-Z0-9_]*$') # aVariable_34

def paramSizeCode(parameter, types, parameters, ret = None):

  aType = findType(parameter.type, types) or findType(parameter.cast, types)
  if not aType:
    return None, None

  format = aType.format
  dim    = aType.dim

  # Parameters with no size expression

  sizeEx = parameter.size
  if not sizeEx:

    # Scalar case.
    if dim == 0:
      return '', ''

    # Special case for null-terminated char (regular/signed/unsigned) array.
    elif dim == 1 and format and format.find('%c') is not -1:
      return '', ''

    # Special case for null-terminated string array.
    elif dim == 1 and format == '%s':
      return '[]', ''

    else:
      return None, None

  # Parameters with size expression

  # Split by *

  if isinstance(sizeEx, int):
    sizeParameters = [sizeEx]
  else:
    sizeParameters = map(str.strip, sizeEx.strip().split('*'))

  sizeFormat = '%d' # Trace supports [], [%d] and [%ld] for arrays.
  code       = []

  for i in sizeParameters:

    # Check if i is an integer

    try:
      code.append('%s' % int(i))
      continue
    except ValueError:
      pass

#    # Check if i is a variable
#
#    if reVariable.match(i):
#      code.append(i)
#      continue

    # Check if i is a conditional expression: a ? b : c

    if reConditional.match(i):
      code.append('(%s)' % i)
      sizeFormat = '%ld'
      continue

    # Check if i is a helper function.
    sizeHelper = helperFuncCode(i)
    if sizeHelper == None:
      return None, None
    elif len(sizeHelper):
      code.append('(%s)' % sizeHelper)
      sizeFormat = '%ld'
      continue

    pFormat = None
    pDim    = None

    # Get format and dim for i.
    if i == 'ret':
      if not ret:
        return None, None
      pName = 'ret'
      rType = findType(ret.type, types)
      if not rType:
        return None, None
      pFormat = rType.format
      pDim    = rType.dim
    else:
      for j in range(len(parameters)):
        param = parameters[j]
        pName = paramNameCode(param.name, j)
        if i == pName:
          sType = findType(param.type, types)
          if not sType:
            return None, None
          pFormat = sType.format
          pDim    = sType.dim
          break

    if not pFormat or pDim is None:
      return None, None

    # Convert size format from %d to %ld.
    if pFormat == '%ld':
      sizeFormat = '%ld'

    if pDim == 0:
      code.append('%s' % i)
    elif pDim == 1:
      code.append('(*%s)' % i)
    else:
      return None, None

  return '[%s]' % sizeFormat, ' * '.join(code)

# Code generation for parameter format.
#   This function uses parameter type.

def paramFormatCode(parameter, types):

  # Find Type using parameter type.
  aType = findType(parameter.type, types)
  if not aType:
    return None

  format = None
  if aType.format and len(aType.format.strip()):
    format = aType.format.strip()

  return format

# Parameter cast.

def paramCast(parameter):

  if parameter.cast and len(parameter.cast.strip()):
    return parameter.cast.strip()

  return None

# Code generation for parameter cast.
#    This function uses parameter cast and Type cast.
#    This is useful for casting an entire array of elements.

def paramCastCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  code = ''
  if aType.cast and len(aType.cast.strip()):
    # If Type has a cast, use that to derive a cast.
    if cType:
      mType = aType.regexc.match(cType).group(0)
    else:
      mType = aType.regexc.match(pType).group(0)
    code  = '(%s) ' % mType.replace(typeStrip(mType), aType.cast.strip())
  elif cType:
    # If parameter has a cast, use that as cast.
    code = '(%s) ' % cType

  return code

# Code generation for parameter type cast.
#   This function uses parameter cast and Type cast.
#   This is useful for casting individual elements of an array.

def paramCastTypeCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  if aType.cast and len(aType.cast.strip()):
    # If Type has a cast, use that as cast.
    return '(%s) ' % aType.cast.strip()

  return ''

# Code generation for parameter cast format.
#   This function uses parameter cast and Type cast.

def paramCastFormatCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return None

  format = None
  if aType.cast and len(aType.cast.strip()):
    # If Type has a cast, use that cast's Type format.
    castType = findType(aType.cast, types)
    if castType and castType.format and len(castType.format.strip()):
      format = castType.format.strip()
  elif cType:
    # If parameter has a cast, use that cast's Type format.
    if aType.format and len(aType.format.strip()):
      format = aType.format.strip()

  return format

# Code generation for parameter format for trace.
#   This function is similar to paramCastFormatCode + handles special cases for trace.

def paramTraceFormatCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return None

  format = None
  if aType.cast and len(aType.cast.strip()):
    # If Type has a cast, use that cast's Type format.
    castType = findType(aType.cast, types)
    if castType and castType.format and len(castType.format.strip()):
      format = castType.format.strip()
  else:
    # Use Type format.
    if aType.format and len(aType.format.strip()):
      format = aType.format.strip()

  # Special handling for trace starts here.

  if not format:
    return None

  # Special handling for %c, %cs, %cu.
  # Handle as integer, strings or binary data
  #
  #   signed char         %c --------> %d         dim=0
  #   signed char         %cs -------> %d         ...
  #   unsigned char       %cu -------> %u
  #   signed char array   %c[] ------> %s         dim=1
  #   signed char array   %cs[] -----> %s         ...
  #   unsigned char array %cu[] -----> %s
  #   signed char array   %c[...] ---> %c[...]
  #   signed char array   %cs[...] --> %c[...]
  #   unsigned char array %cu[...] --> %c[...]
  #   [Undefined]                                 dim>1

  if format.find('%c') is not -1:

    # If it's a scalar, treat as integer
    if aType.dim == 0:
      if format == '%cu':
        return '%u'
      else:
        return '%d'

    # If it's an unsized array, treat as string
    # If it's binary and known size, treat as unsigned char array
    # otherwise char array.

    if aType.dim == 1:
      if not parameter.size:
        return '%s'
      if parameter.binary:
        return '%cu'
      else:
        return '%c'

    print 'Warning: %c not supported with dim > 1.'
    return None

  return format

# Code generation for parameter cast for trace.
#   This function is similar to paramCastCode + handles special cases for trace.

def paramTraceCastCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  code = ''
  if aType.cast and len(aType.cast.strip()):
    # If Type has a cast, use that to derive a cast.
    if cType:
      mType = aType.regexc.match(cType).group(0)
    else:
      mType = aType.regexc.match(pType).group(0)
    code = '(%s) ' % mType.replace(typeStrip(mType), aType.cast.strip())
  elif cType:
    # If parameter has a cast, use that as cast.
    code = '(%s) ' % cType

  # Special handling for trace starts here.

  # Since trace uses format specification for casting, we do not need to explicitly cast.
  if cType:
    code = ''

  # Note: If we do not want to support a cast, set code to None.

  # Special handling for %c, %cs, %cu of non-pointer type.
  if aType.format and aType.format.find('%c') is not -1 and aType.dim == 0:
    if aType.format == '%cu':
      code = '(unsigned int) '
    else:
      code = '(int) '

  return code

# Code generation for parameter default value.

def paramDefaultCode(pType, types = typesBasic):

  # Check if Type has a default value.
  aType = findType(pType, types)
  if aType and aType.dim < 1 and aType.default and len(aType.default.strip()):
    return '%s' % aType.default.strip()

  rType = pType.strip()

  if rType.endswith('*'):
    return 'NULL'

  if rType in ['signed', 'signed int', 'int']:
    return '0'

  if rType in ['unsigned', 'unsigned int']:
    return '0u'

  return '(%s) 0' % rType

# Code generation for parameter base type.
#   This function uses parameter cast and Type baseType.

def paramBaseTypeCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  code = ''
  if aType.baseType and len(aType.baseType.strip()):
    # If Type has a baseType, use that as base type.
    code = aType.baseType.strip()
  elif cType:
    # If parameter has a cast, use that to derive a base type.
    code = typeStrip(cType)
  else:
    # Use parameter type to derive a base type.
    code = typeStrip(pType)

  # Special case for char **.
  if cType:
    if reCharPtrPtr.match(cType):
      return 'cgiArgs'
  else:
    if reCharPtrPtr.match(pType):
      return 'cgiArgs'

  return code

# Code generation for parameter base type using proxy type.
#   This function uses parameter cast, Type baseType, and Type proxyType.
#   This is similar to paramBaseTypeCode + uses Type proxyType.

def paramProxyBaseTypeCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  code = ''
  if aType.proxyType and len(aType.proxyType.strip()):
    # If Type has a proxyType, use that proxyType.
    if cType:
      mType = aType.regexc.match(cType).group(0)
    else:
      mType = aType.regexc.match(pType).group(0)
    proxyType = findType(mType.replace(typeStrip(mType), aType.proxyType.strip()), types)
    if proxyType:
      # If proxyType Type found, use that Type's baseType.
      code = proxyType.baseType.strip()
    else:
      # If proxyType Type not found, use proxyType to drive a base type.
      code = typeStrip(aType.proxyType)
  elif aType.baseType and len(aType.baseType.strip()):
    # If Type has a baseType, use that as a base type.
    code = aType.baseType.strip()
  elif cType:
    # If parameter has a cast, use that to derive a base type.
    code = typeStrip(cType)
  else:
    # Use parameter type to derive a base type.
    code = typeStrip(pType)

  # Special case for char **.
  if cType:
    if reCharPtrPtr.match(cType):
      return 'cgiArgs'
  else:
    if reCharPtrPtr.match(pType):
      return 'cgiArgs'

  # Special case for void *
  if cType:
    if reVoidPtr.match(cType):
      return cType
  else:
    if reVoidPtr.match(pType):
      return pType

  return code

# Code generation for parameter proxy format.
#   This function uses parameter cast and Type proxyType.
#   This is similar to paramCastFormatCode + uses Type proxyType instead of Type cast.

def paramProxyFormatCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return None

  format = None
  if aType.proxyType and len(aType.proxyType.strip()):
    # If Type has a proxyType, use that proxyType's Type format.
    if cType:
      mType = aType.regexc.match(cType).group(0)
    else:
      mType = aType.regexc.match(pType).group(0)
    proxyType = findType(mType.replace(typeStrip(mType), aType.proxyType.strip()), types)
    if proxyType and proxyType.format and len(proxyType.format.strip()):
      format = proxyType.format.strip()
  else:
    # Use Type format.
    if aType.format and len(aType.format.strip()):
      format = aType.format.strip()

  return format

# Code generation for parameter proxy type.
#   This function uses parameter cast and Type proxyType.
#   This is similar to paramCastCode + uses Type proxyType instead of Type cast.

def paramProxyTypeCode(parameter, types = typesBasic):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = parameter.type.strip()
    aType = findType(pType, types)
  if not aType:
    return ''

  code = ''
  if aType.proxyType and len(aType.proxyType.strip()):
    # If Type has a proxyType, use that to derive a proxy type.
    if cType:
      mType = aType.regexc.match(cType).group(0)
    else:
      mType = aType.regexc.match(pType).group(0)
    code = mType.replace(typeStrip(mType), aType.proxyType.strip())
  elif cType:
    # If parameter has a cast, use that as proxy type.
    code = cType

  return code

# Code generation for parameter declaration.

def paramDeclCode(parameter, types = typesBasic, size = None, name = None):

  pType = typeCode(parameter.type)
  aType = findType(pType, types)

  # Check max size for array.
  maxSize = parameter.maxSize
  if not maxSize:
    maxSize = size

  # Check for an integer size for array.
  intSize = None
  try:
    intSize = int(maxSize)
  except ValueError:
    pass

  # If no input <name>, use parameter name.
  if not name:
    name = parameter.name.strip()

  decl = None
  if aType.dim > 0 and pType[-1] == '*':
    # Array case.
    declType = pType[:-1]
    if intSize:
      # Use static array for integer sized array.
      decl = 'static %s%s[%d];' % (declType, name, intSize)
    else:
      # Use boost scoped_array for non-integer sized array.
      decl = 'boost::scoped_array<%s> %s(new %s[%s]);' % (declType.strip(), name, declType, maxSize)
  else:
    # Scalar case.
    decl = '%s%s;' % (pType, name)

  return decl

# Code generation for parameter declaration.
#   This function uses parameter cast.
#   This is similar to paramDeclCode + uses parameter cast.

def paramCastDeclCode(parameter, types = typesBasic, size = None, name = None):

  cType = paramCast(parameter)

  # Find Type using parameter cast or parameter type.
  if cType:
    aType = findType(cType, types)
  else:
    pType = typeCode(parameter.type)
    aType = findType(pType, types)
  if not aType:
    return None

  # Check max size for array.
  maxSize = parameter.maxSize
  if not maxSize:
    maxSize = size

  # Check for an integer size for array.
  intSize = None
  try:
    intSize = int(maxSize)
  except ValueError:
    pass

  # If no input <name>, use parameter name.
  if not name:
    name = parameter.name.strip()

  decl = None
  if cType:
    # If parameter has a cast, use that cast type.
    if aType.dim > 0 and cType[-1] == '*':
      # Array case.
      declType = cType[:-1]
      if intSize:
        # Use static array for integer sized array.
        decl  = 'static %s%s[%d];' % (declType, name, intSize)
      else:
        # Use boost scoped_array for non-integer sized array.
        decl  = 'boost::scoped_array<%s> ' % declType.strip()
        decl += '%s(new %s[%s]);' % (name, declType, maxSize)
    else:
      # Scalar case.
      decl = '%s%s;' % (cType, name)
  else:
    # Use parameter type.
    if aType.dim > 0 and pType[-1] == '*':
      # Array case.
      declType = pType[:-1]
      if intSize:
        # Use static array for integer sized array.
        decl  = 'static %s%s[%d];' % (declType, name, intSize)
      else:
        # Use boost scoped_array for non-integer sized array.
        decl  = 'boost::scoped_array<%s> ' % declType.strip()
        decl += '%s(new %s[%s]);' % (name, declType, maxSize)
    else:
      # Scalar case.
      decl = '%s%s;' % (pType, name)

  return decl

# Code generation for parameter state lookup.
#   Uses parameter's lookup attribute or parameter's state type's state attribute.
#   Note: key and pSize inputs are not relevant for lookup via lookup attribute.

def paramStateMapCode(parameter, stateType, key, value, pSize = '', stateWarn = ''):

  lookup = getattr(parameter, 'lookup', None)
  state  = getattr(stateType, 'state',  None)

  # Obtain core type for state.
  pType = typeCode(parameter.type)
  sType = pType.replace('const', '').replace('  ', ' ').strip(' *')

  default = getattr(stateType, 'default', '0')

  lines = []
  if stateType.dim == 0:

    # Scalar case.

    if lookup:

      # Use lookup attribute for parameter.

      lookupCode = lookup
      lookupHelper = helperFuncCode(lookupCode)
      if lookupHelper:
        lookupCode = lookupHelper
      lines.append('%s%s = %s;' % (pType, value, lookupCode))

    else:

      # Use state attribute from parameter's state type.

      lines.append('%s%s = lookup<%s>(%s, %s, %s);' % (pType, value, sType, state, key, default))

    # Check if valid state value.

    lines.append('if (%s && !%s)' % (key, value))
    lines.append('{')
    if len(stateWarn):
      lines.append('  %s' % stateWarn)
    lines.append('  return false;')
    lines.append('}')

  elif stateType.dim == 1 and len(pSize):

    # 1D array case.

    valueDecl = paramDeclCode(parameter, [stateType], pSize, value)
    valueDecl = valueDecl.replace('const ', '')

    # Declare variable for state values.

    lines.append('%s' % valueDecl)
    lines.append('if (!%s)' % key)
    lines.append('  %s.reset();' % value)
    lines.append('else')
    lines.append('{')

    if lookup:

      # Use lookup attribute of parameter.

      lookupCode = lookup
      lookupHelper = helperFuncCode(lookupCode)
      if lookupHelper:
        lookupCode = lookupHelper
      lines.append('  %s.reset(%s);' % (value, lookupCode))

      # Check if valid state values in array.

      lines.append('  if ((%s) && !%s.get())' % (pSize, value))
      lines.append('  {')
      if len(stateWarn):
        lines.append('    %s' % stateWarn)
      lines.append('    return false;')
      lines.append('  }')

    else:

      # Use state attribute from parameter's state type.

      lines.append('  for (size_t _i = 0; _i < size_t(%s); ++_i)' % pSize)
      lines.append('  {')

      # Lookup state value for each array element and check if valid.

      lines.append('    %s[_i] = lookup<%s>(%s, %s[_i], %s);' % (value, sType, state, key, default))
      lines.append('    if (%s[_i] && !%s[_i])' % (key, value))
      lines.append('    {')
      if len(stateWarn):
        lines.append('      %s' % stateWarn)
      lines.append('      return false;')
      lines.append('    }')

      lines.append('  }')

    lines.append('}')

  else:

    # Arrays with dim > 1 or with no size expression are not supported.

    print 'unsupported type for state lookup'

  return lines

# Code generation for parameter state update.

def paramStateUpdateCode(parameter, stateType, key, value, pSize = '', stateWarn = ''):

  # Check if parameter's state type has a state attribute.
  state = getattr(stateType, 'state', None)
  if not state:
    print 'parameter has no state attribute for state update'
    return []

  # Obtain core type for state.
  pType = typeCode(parameter.type)
  sType = pType.replace('const', '').replace('  ', ' ').strip(' *')

  default = getattr(stateType, 'default', '0')

  lines = []
  if stateType.dim == 0:

    # Scalar case.

    updateCode = 'update<%s>(%s, %s, %s, %s)' % (sType, state, key, value, default)
    if len(stateWarn):
      lines.append('if (!%s)' % updateCode)
      lines.append('  %s' % stateWarn)
    else:
      lines.append('%s;' % updateCode)

  elif stateType.dim == 1 and len(pSize):

    # 1D array case.

    updateCode = 'update<%s>(%s, %s[_i], %s[_i], %s)' % (sType, state, key, value, default)
    lines.append('if (%s && %s)' % (key, value))
    lines.append('{')
    lines.append('  for (size_t _i = 0; _i < size_t(%s); ++_i)' % pSize)
    if len(stateWarn):
      lines.append('  {')
      lines.append('    if (!%s)' % updateCode)
      lines.append('      %s' % stateWarn)
      lines.append('  }')
    else:
      lines.append('  %s;' % updateCode)
    lines.append('}')

  else:

    # Arrays with dim > 1 or with no size expression are not supported.

    print 'unsupported type for state update'

  return lines

# Code generation for parameter intercept type.

def paramInterceptTypeCode(parameter, types = typesBasic):

  if not getattr(parameter, 'intercept', None):
    return None

  aType = findType(parameter.type, types)
  if not aType:
    return None

  return aType

# Regex for parameter intercept attribute.

reIntercept = re.compile('^\s*(?P<name>[\w-]+)\s*\((?P<param>.*)\)\s*$')

# Code generation for parameter intercept input declaration an and optional initialization.
#   This function uses the intercept attribute for initialization.

def paramInterceptInputCode(parameter, interceptType, pSize = None, name = None, pDefault = '0',  cMode = False):

  # Find Type using parameter type.
  pType = typeCode(parameter.type)
  if not interceptType:
    return None, []

  # Obtain core type for state.
  sType = pType.replace('const', '').replace('  ', ' ').strip(' *')

  # Check max size for array.
  maxSize = parameter.maxSize
  if not maxSize:
    maxSize = pSize

  # Check for an integer size for array.
  intSize = None
  try:
    intSize = int(maxSize)
  except ValueError:
    pass

  # If no input <name>, use parameter name.
  if not name:
    name = parameter.name.strip()

  # Get the intercept value for initialization.

  interceptAttr = getattr(parameter, 'intercept')
  # Intercept function of the form Name(Param)
  interceptFunc = reIntercept.match(interceptAttr)
  if interceptFunc:
    interceptName  = interceptFunc.group('name')
    interceptParam = interceptFunc.group('param')

  interceptHelper = helperFuncCode(interceptAttr)
  if interceptHelper:
    interceptValue = interceptHelper
  elif interceptFunc:
    pName = name.replace('intercept_', '')
    if cMode:
      interceptValue = '%s ? &(cb_%s) : NULL' % (pName, interceptName)
    else:
      interceptValue = '%s ? &(::cb_%s) : NULL' % (pName, interceptName)
  else:
    interceptValue = interceptAttr

  interceptDecl   = ''
  interceptFree   = ''
  interceptAssign = []
  interceptUpdate = []

  if interceptType.dim == 0:

    # Scalar case.

    if cMode:

      # Intercept declare (C).

      if pDefault:
        interceptDecl = '%s%s = %s;' % (pType, name, pDefault)
      else:
        interceptDecl = '%s%s;' % (pType, name)

      # Intercept assign (C)

      if interceptValue:
        interceptAssign.append('%s = %s;' % (name, interceptValue))

    else:

      # Intercept delcare and assign (C++).

      if interceptValue:
        interceptDecl = '%s%s = %s;' % (pType, name, interceptValue)
      else:
        interceptDecl = '%s%s;' % (pType, name)

    # Intercept update.

    if not interceptHelper and interceptFunc:
      pName = name.replace('intercept_', '')
      if cMode:
        interceptUpdate.append('update%s(&_state.%sMap, %s, %s);' % (sType, interceptName, interceptParam, pName))
      else:
        interceptUpdate.append('update%s(_state.%sMap, %s, %s);' % (sType, interceptName, interceptParam, pName))

  elif interceptType.dim == 1 and pType[:-1] == '*' and pSize:

    # 1D array case.

    declType = pType[:-1]
    if intSize:

      # Use static array for integer sized array.

      if cMode:

        # Intercept declare (C).

        # TODO: Add initialization?
        interceptDecl = 'static %s%s[%d];' % (declType, name, intSize)

        # Intercept assign (C).

        if interceptValue:
          interceptAssign.append('%s = %s;' % (name, interceptValue))

      else:

        # Intercept declare and assign (C++).

        if interceptValue:
          interceptDecl = 'static %s%s[%d] = %s;' % (declType, name, intSize, interceptValue)
        else:
          interceptDecl = 'static %s%s[%d];' % (declType, name, intSize)

    else:

      if cMode:

        # Intercept declare (C).

        if pDefault:
          interceptDecl = '%s*%s = %s;' % (declType, name, pDefault)
        else:
          interceptDecl = '%s*%s;' % (declType, name)

        # Intercept assign (C).

        # TODO: Assign arrays in C.

        # Intercept free (C).

        # TODO: Free arrays in C.

      else:

        # Use boot scoped_array for non-integer sized array (C++).

        if interceptValue:
          interceptDecl = 'boost::scoped_array<%s> %s(%s);' % (declType.strip(), name, interceptValue)
        else:
          interceptDecl = 'boost::scoped_array<%s> %s(new %s[%s]);' % (declType.strip(), name, declType, maxSize)

    # Intercept update. # TODO: Not supported for now.

  return interceptDecl, interceptFree, interceptAssign, interceptUpdate

# Code generation for parameter intercept output declaration an and optional initialization.
#   This function uses the intercept attribute for initialization.

def paramInterceptOutputCode(parameter, interceptType, pSize = None, name = None, pDefault = '0', cMode = False):

  # Find Type using parameter type.
  pType = typeCode(parameter.type)
  if not interceptType:
    return None

  # Obtain core type for state.
  sType = pType.replace('const', '').replace('  ', ' ').strip(' *')

  # Check max size for array.
  maxSize = parameter.maxSize
  if not maxSize:
    maxSize = pSize

  # Check for an integer size for array.
  intSize = None
  try:
    intSize = int(maxSize)
  except ValueError:
    pass

  # If no input <name>, use parameter name.
  if not name:
    name = parameter.name.strip()

  # Get the intercept value for initialization.

  interceptValue = getattr(parameter, 'intercept')
  # Intercept function of the form Name(Param)
  interceptFunc = reIntercept.match(interceptValue)
  if interceptFunc:
    interceptName  = interceptFunc.group('name')
    interceptParam = interceptFunc.group('param')

  interceptHelper = helperFuncCode(interceptValue)
  if interceptHelper:
    interceptValue = interceptHelper
  elif interceptFunc:
    pName = name.replace('intercept_', '')
    interceptValue = 'lookup%s(_state.%sMap, %s)' % (sType, interceptName, interceptParam)

  interceptDecl   = ''
  interceptFree   = ''
  interceptAssign = []

  if interceptType.dim == 0:

    # Scalar case.

    if cMode:

      # Intercept declare (C).

      if pDefault:
        interceptDecl = '%s%s = %s;' % (pType, name, pDefault)
      else:
        interceptDecl = '%s%s;' % (pType, name)

      # Intercept assign (C).

      if interceptValue:
        interceptAssign.append('%s = %s;' % (name, interceptValue))

    else:

      # Intercept declare and assign (C++).

      if interceptValue:
        interceptDecl = '%s%s = %s;' % (pType, name, interceptValue)
      else:
        interceptDecl = '%s%s;' % (pType, name)

  elif interceptType.dim == 1 and pType[:-1] == '*' and pSize:

    # 1D array case.

    declType = pType[:-1]
    if intSize:

      # Use static array for integer sized array.

      if cMode:

        # Intercept declare (C)

        # TODO: Add initialization?
        interceptDecl = 'static %s%s[%d];' % (declType, name, intSize)

        # Intercept assign (C).

        if interceptValue:
          interceptAssign.append('%s = %s;' % (name, interceptValue))

      else:

        # Intercept declare and assign (C++).

        if interceptValue:
          interceptDecl = 'static %s%s[%d] = %s;' % (declType, name, intSize, interceptValue)
        else:
          interceptDecl = 'static %s%s[%d];' % (declType, name, intSize)

    else:

      if cMode:

        # Intercept delcare (C).

        if pDefault:
          interceptDecl = '%s*%s = %s;' % (declType, name, pDefault)
        else:
          interceptDecl = '%s*%s;' % (declType, name)

        # Intercept assign (C).

        # TODO: Assign arrays in C.

        # Intercept free (C).

        # TODO: Free arrays in C.

      else:

        # Use boot scoped_array for non-integer sized array (C++).

        if interceptValue:
          interceptDecl = 'boost::scoped_array<%s> %s(%s);' % (declType.strip(), name, interceptValue)
        else:
          interceptDecl = 'boost::scoped_array<%s> %s(new %s[%s]);' % (declType.strip(), name, declType, maxSize)

  return interceptDecl, interceptFree, interceptAssign
