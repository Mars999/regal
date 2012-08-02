#!/usr/bin/python

import re

# Class Type:
#   regexc:    regular expression for matching type expression.
#   format:    format for trace purpose.
#   dim:       num of dim, 0 is scalar. Default is 0.
#   cast:      casting of a type for trace purpose.
#   baseType:  base type for cgiReference type purpose.
#   proxyType: proxy type for cgiEncode/cgiDecode purpose.
#   default:   default/initialization value for typedef.

class Type:

  def __init__(self, regex, format = '', dim = 0, cast = None, baseType = None, proxyType = None, default = None):

    self.regexc    = re.compile(regex)
    self.format    = format
    self.dim       = dim
    self.cast      = cast
    self.baseType  = baseType
    self.proxyType = proxyType
    self.default   = default

# Type regex expressions.

typeStdPat    = '^\s*(const)*\s*(%s)\s*(const)*\s*$'
typePtrPat    = '^\s*(const)*\s*(%s)\s*(const)*\s*\*\s*(const)*\s*$'
typeRefStdPat = typeStdPat % '(&)*\\s*(%s)'
typeRefPtrPat = typePtrPat % '(&)*\\s*(%s)'

# Basic Types

typesBasic = []
typesBasic.append(Type(typeStdPat    % '(void)',                                    None,   dim =-1, baseType = None                  ))
typesBasic.append(Type(typePtrPat    % '(void)',                                    '%p',            baseType = 'void'                ))
typesBasic.append(Type(typePtrPat    % '(void)\\s*(const)*\\s*\\*',                 None,   dim = 1, baseType = 'void'                ))
typesBasic.append(Type(typeRefStdPat % '(signed)\\s*(char)',                        '%cs',           baseType = 'signed char'         ))
typesBasic.append(Type(typeRefStdPat % '(unsigned)\\s*(char)',                      '%cu',           baseType = 'unsigned char'       ))
typesBasic.append(Type(typeRefStdPat % '(char)',                                    '%c',            baseType = 'char'                ))
typesBasic.append(Type(typeRefStdPat % '(signed)*\\s*(short)\\s*(int)*',            '%hd',           baseType = 'short'               ))
typesBasic.append(Type(typeRefPtrPat % '(signed)*\\s*(short)\\s*(int)*',            '%hd',  dim = 1, baseType = 'short'               ))
typesBasic.append(Type(typeRefStdPat % '(signed)*\\s*(long)\\s*(int)*',             '%ld',           baseType = 'long'                ))
typesBasic.append(Type(typeRefPtrPat % '(signed)*\\s*(long)\\s*(int)*',             '%ld',  dim = 1, baseType = 'long'                ))
typesBasic.append(Type(typeRefStdPat % '(signed)*\\s*(long)\\s*(long)\\s*(int)*',   '%lld',          baseType = 'long long'           ))
typesBasic.append(Type(typeRefPtrPat % '(signed)*\\s*(long)\\s*(long)\\s*(int)*',   '%lld', dim = 1, baseType = 'long long'           ))
typesBasic.append(Type(typeRefStdPat % '(signed)*\\s*(int)',                        '%d',            baseType = 'int'                 ))
typesBasic.append(Type(typeRefPtrPat % '(signed)*\\s*(int)',                        '%d',   dim = 1, baseType = 'int'                 ))
typesBasic.append(Type(typeRefStdPat % '(unsigned)\\s*(short)\\s*(int)*',           '%hu',           baseType = 'unsigned short'      ))
typesBasic.append(Type(typeRefPtrPat % '(unsigned)\\s*(short)\\s*(int)*',           '%hu',  dim = 1, baseType = 'unsigned short'      ))
typesBasic.append(Type(typeRefStdPat % '(unsigned)\\s*(long)\\s*(int)*',            '%lu',           baseType = 'unsigned long'       ))
typesBasic.append(Type(typeRefPtrPat % '(unsigned)\\s*(long)\\s*(int)*',            '%lu',  dim = 1, baseType = 'unsigned long'       ))
typesBasic.append(Type(typeRefStdPat % '(unsigned)*\\s*(long)\\s*(long)\\s*(int)*', '%lld',          baseType = 'unsigned long long'  ))
typesBasic.append(Type(typeRefPtrPat % '(unsigned)*\\s*(long)\\s*(long)\\s*(int)*', '%lld', dim = 1, baseType = 'unsigned long long'  ))
typesBasic.append(Type(typeRefStdPat % '(unsigned)\\s*(int)*',                      '%u',            baseType = 'unsigned int'        ))
typesBasic.append(Type(typeRefPtrPat % '(unsigned)\\s*(int)*',                      '%u',   dim = 1, baseType = 'unsigned int'        ))
typesBasic.append(Type(typeRefStdPat % '(size_t)',                                  '%zu',           baseType = 'size_t'              ))
typesBasic.append(Type(typeRefPtrPat % '(size_t)',                                  '%zu',  dim = 1, baseType = 'size_t'              ))
typesBasic.append(Type(typeRefStdPat % '(ptrdiff_t)',                               '%z',            baseType = 'ptrdiff_t'           ))
typesBasic.append(Type(typeRefPtrPat % '(ptrdiff_t)',                               '%z',   dim = 1, baseType = 'ptrdiff_t'           ))
typesBasic.append(Type(typeRefStdPat % '(long)\\s*(double)',                        '%Lf',           baseType = 'long double'         ))
typesBasic.append(Type(typeRefPtrPat % '(long)\\s*(double)',                        '%Lf',  dim = 1, baseType = 'long double'         ))
typesBasic.append(Type(typeRefStdPat % '(double)',                                  '%lf',           baseType = 'double'              ))
typesBasic.append(Type(typeRefPtrPat % '(double)',                                  '%lf',  dim = 1, baseType = 'double'              ))
typesBasic.append(Type(typeRefStdPat % '(float)',                                   '%f',            baseType = 'float'               ))
typesBasic.append(Type(typeRefPtrPat % '(float)',                                   '%f',   dim = 1, baseType = 'float'               ))
typesBasic.append(Type(typeStdPat    % '(signed)\\s*(char)\\s*(const)*\\s*\\*',     '%cs',  dim = 1, baseType = 'signed char'         ))
typesBasic.append(Type(typeStdPat    % '(unsigned)\\s*(char)\\s*(const)*\\s*\\*',   '%cu',  dim = 1, baseType = 'unsigned char'       ))
typesBasic.append(Type(typeStdPat    % '(char)\\s*(const)*\\s*\\*',                 '%c',   dim = 1, baseType = 'const char *'        ))
typesBasic.append(Type(typePtrPat    % '(char)\\s*(const)*\\s*\\*',                 '%s',   dim = 1, baseType = 'const char * const *'))

# Find state for <typeName> using <states>.
#   states := [ ('<type name>', '<state map name>'), ... ]

def findState(typeName, states = None):

  for stateItem in states:
    if stateItem[0].strip() == typeName.strip():
      return stateItem[1].strip()

  return None

# Generate Types from <enum> Enum.

def typesFromEnum(enum, states = None):

  name = enum.name.strip()

  enumStd = Type(typeRefStdPat % name, '%lu',          baseType = name, default = enum.default)
  enumPtr = Type(typeRefPtrPat % name, '%lu', dim = 1, baseType = name, default = enum.default)

  # Find state and add state information to the new types.

  if states:
    stateValue = findState(enum.name, states)
    if stateValue:
      enumStd.state = stateValue
      enumPtr.state = stateValue

  enumTypes = []
  enumTypes.append(enumStd)
  enumTypes.append(enumPtr)

  return enumTypes

# Generate Types from <typedef> Typedef.

def typesFromTypedef(typedef, types = typesBasic, states = None):

  # Ignore function pointer types with no typeCast for now.

  if len(typedef.function) and not hasattr(typedef, 'typeCast'):
    return []

  name = typedef.name.strip()

  # Check for typeCast, baseType, proxyType, default attributes.

  typeCast = getattr(typedef, 'typeCast', None)
  if typeCast and not len(typeCast.strip()):
    typeCast = None

  baseType = getattr(typedef, 'baseType', None)
  if not baseType or not len(baseType.strip()):
    baseType = name

  proxyType = getattr(typedef, 'proxyType', None)
  if proxyType and not len(proxyType.strip()):
    proxyType = None

  typeDefault = getattr(typedef, 'default', None)
  if typeDefault and not len(typeDefault.strip()):
    typeDefault = None

  # Match type using typeCast if typeCast present or using typedef value.

  if typeCast:
    typeMatchStd = typeCast
  else:
    typeMatchStd = typedef.type.strip()
  typeMatchPtr = '%s *' % typeMatchStd

  # Try to find a matching type using typeMatchStd.

  typeStd = None
  for aType in types:
    if aType.regexc.match(typeMatchStd):
      typeStd = Type(typeRefStdPat % name, aType.format, dim = aType.dim, cast = typeCast, baseType = baseType, proxyType = proxyType, default = typeDefault)
      break

  # Try to find a matching pointer type using typeMatchPtr.

  typePtr = None
  for aType in types:
    if aType.regexc.match(typeMatchPtr):
      typePtr = Type(typeRefPtrPat % name, aType.format, dim = aType.dim, cast = typeCast, baseType = baseType, proxyType = proxyType, default = typeDefault)
      break

  # Try to find a matching pointer type using typeStd with dim += 1.

  if not typePtr and typeStd:
    typePtr = Type(typeRefPtrPat % name, typeStd.format, dim = typeStd.dim + 1, cast = typeCast, baseType = baseType, proxyType = proxyType, default = typeDefault)

  # Find state and add state information to the new types.

  if states:
    stateValue = findState(typedef.name, states)
    if stateValue:
      typeStd.state = stateValue
      typePtr.state = stateValue

  typedefTypes = []
  if typeStd and typePtr:
    typedefTypes.append(typeStd)
    typedefTypes.append(typePtr)

  return typedefTypes

# Generate types for each api.

def apiTypes(apis, states = None):

  for api in apis:

    # Initialize types to the basic types.

    types = []
    types.extend(typesBasic)

    # Obtain state types as an attribute.

    if not states:
      states = getattr(api, 'states', None)

    # Add enum types.

    if api and api.enums:
      for enum in api.enums:
        types.extend(typesFromEnum(enum, states))

    # Add typedef types.

    if api and api.typedefs:
      for typedef in api.typedefs:
        types.extend(typesFromTypedef(typedef, types, states))

    # Assign types as an attribute.

    api.types = types

# Find type using <typeFormat> match with regex expressions for <types>.

def findType(typeFormat, types = typesBasic):

  if typeFormat:
    for aType in types:
      if aType.regexc.match(typeFormat.strip()):
        return aType

  return None

# Strip typeFormat to the core type.

def typeStrip(typeFormat):

  # Replace const, *, & with spaces.
  pType = typeFormat.replace('const ', ' ').replace('&', ' ').replace('*', ' ')

  # Remove extraneous spaces.
  pType = pType.replace('  ', ' ').strip()

  return pType

# Return Type for parameter's type if it has state information.

def paramStateType(parameter, types = typesBasic):

  aType = findType(parameter.type, types)
  if not aType:
    return None

  lookup = getattr(parameter, 'lookup', None)
  if lookup or hasattr(aType, 'state'):
    return aType

  return None
