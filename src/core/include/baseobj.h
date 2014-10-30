/*

HyPhy - Hypothesis Testing Using Phylogenies.

Copyright (C) 1997-now
Core Developers:
  Sergei L Kosakovsky Pond (spond@ucsd.edu)
  Art FY Poon    (apoon@cfenet.ubc.ca)
  Steven Weaver (sweaver@ucsd.edu)

Module Developers:
	Lance Hepler (nlhepler@gmail.com)
	Martin Smith (martin.audacis@gmail.com)

Significant contributions from:
  Spencer V Muse (muse@stat.ncsu.edu)
  Simon DW Frost (sdf22@cam.ac.uk)

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef _HBASEOBJ_
#define _HBASEOBJ_
//#pragma once

typedef char *Ptr;
typedef double _Parameter;

#include "defines.h"

#include "stdio.h"

//base object class
class BaseObj {

private:
  long nInstances;

public:

  BaseObj();

  virtual ~BaseObj(void) {}

  virtual BaseObj *toStr (void) const;

  virtual BaseObj *toErrStr (void) const;

  virtual void toFileStr (FILE *) const;

  virtual BaseObj *makeDynamic(void) const = 0;

  virtual void Initialize(bool = false) { nInstances = 1L; }

  virtual void Duplicate(BaseObj const * ref) = 0;

  inline void AddAReference(void) { nInstances++; }

  inline void RemoveAReference(void) { nInstances--; }
  
  inline bool CanFreeMe (void)  const { return nInstances <= 1; }
  
  inline bool SingleReference (void)  const { return nInstances == 1; }
    // comparison functions
  
  static void DeleteObject (BaseObj * ref);
};

typedef BaseObj *BaseRef;
typedef BaseObj const * BaseRefConst;

#ifdef _SLKP_USE_SSE_INTRINSICS
  #include <pmmintrin.h>
#endif

#ifdef _SLKP_USE_AVX_INTRINSICS
  #include <immintrin.h>
#endif

#endif

//EOF
