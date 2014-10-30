/*

HyPhy - Hypothesis Testing Using Phylogenies.

Copyright (C) 1997-2007

Primary Development:
  Sergei L Kosakovsky Pond (sergeilkp@mac.com)
Significant contributions from:
  Spencer V Muse (muse@stat.ncsu.edu)
  Simon DW Frost (sdfrost@ucsd.edu)
  Art FY Poon    (apoon@biomail.ucsd.edu)

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

#include    "baseobj.h"
#include    "hy_strings.h"


BaseObj::BaseObj() { nInstances = 1; }

//______________________________________________________________________________
BaseRef BaseObj::toStr(void) const { return new _String("<HyPhy Base Object>"); }

//______________________________________________________________________________
BaseRef BaseObj::toErrStr(void) const { return toStr(); }

//______________________________________________________________________________
void BaseObj::toFileStr(FILE *dest) const {
  _String *s = (_String *)toStr();
  fwrite(s->getStr(), 1, s->Length(), dest);
  delete s;
}

//______________________________________________________________________________
void BaseObj::DeleteObject (BaseObj * ref) {
  if (ref) {
    if (ref->CanFreeMe()) {
      delete ref;
    } else {
      ref->RemoveAReference();
    }
  }
}

