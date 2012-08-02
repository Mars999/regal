#!/usr/bin/python

import ApiCodeFilter

# Import attribute <name> from module <name>

def importAttr(name):

  attr = getattr(__import__(name), name)
  return attr

# Output code to output file.

def outputCode(filename, code):

  code = codeJoin(code)

  code = ApiCodeFilter.expandtabs(code)
  code = ApiCodeFilter.trim(code)
  code = ApiCodeFilter.foldIfs(code)
  code = ApiCodeFilter.foldPreprocessorIfs(code)
  code = ApiCodeFilter.foldEmptyLines(code)
  code = ApiCodeFilter.foldImpossibleBreak(code)
  code = ApiCodeFilter.foldImpossibleReturn(code)
  code = ApiCodeFilter.foldRedundantCase(code)

  # Compare code with current file.

  try:

    # Read current file.

    current = open(filename, 'r')
    currentCode = current.read()
    current.close()

    # Compare code.

    if currentCode == code:
      print 'File skipped: %s' % filename
      return

  except IOError:

    # Current file does not exist.

    print 'File created: %s' % filename

  # Output code to file.

  try:

    output = open(filename, 'w')
    output.write(code)
    output.close()

    print 'File updated: %s' % filename

  except IOError:

    # File not found or file is read-only.

    print 'File read-only: %s' % filename

# Check if <version> is valid wrt <outputVersion>

def validVersion(version, outputVersion):

  if isinstance(version, int) or isinstance(version, float):
    if float(version) > outputVersion:
      return False

  return True

# Determine the maximum of some aspect of a collection of items

def maxLength(collection, aspect):
  ret = 0
  if collection is not None:
    for i in collection:
      if not i is None:
        if not aspect(i) is None:
          ret = max(ret,aspect(i))
  return ret

# Tidy-up code in list-of-strings format
#   - Break multi-line strings into seperate strings
#   - Strip extraneous whitespace from the end of each line
#   - Collapse multiple empty lines into one

def codeTidy(lines):

  # In the first pass, deal with multi-line strings
  tmp = []
  for i in lines:
    for j in i.split('\n'):
      tmp.append(j.rstrip())

  # In the second pass, fold consecutive empty lines
  ret = []
  skipping = False
  for i in tmp:
    if not len(i):
      if skipping:
        continue
      else:
        skipping = True
    else:
      skipping = False
    ret.append(i)

  return ret

# Join list-of-strings code into a string

def codeJoin(lines):
  if lines==None or len(lines)==0:
    return ''

  if not isinstance(lines,list):
    lines = [lines]

  return '\n'.join(codeTidy(lines))

# Value as hex string, if possible

def hexValue(value,format = '0x%x'):

  if isinstance(value, str) or isinstance(value, unicode):
    try:
      value = long(value)
    except:
      pass

  if isinstance(value, int) or isinstance(value, long):
    return format%(value)

  return value

# Value to long, if possible, otherwise None

def toLong(value):
  tmp = 0
  try:
    tmp = long(value)
  except:
    return None
  return tmp

# void type?

def typeIsVoid(t):
  t = t.strip()
  return t=='void' or t=='VOID'
