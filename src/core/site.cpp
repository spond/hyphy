/*

 HyPhy - Hypothesis Testing Using Phylogenies.
 
 Copyright (C) 1997-now
 Core Developers:
 Sergei L Kosakovsky Pond (spond@ucsd.edu)
 Steven Weaver (sweaver@ucsd.edu)
 Martin Smith (martin.audacis@gmail.com)
 
 Module Developers:
 Art FY Poon    (apoon@cfenet.ubc.ca)
 Lance Hepler (nlhepler@gmail.com)
 
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

#include "site.h"
#include "helperfunctions.h"
#include "errorfns.h"


#include <string.h> // for memcpy


//______________________________________________________________________________
_Site::_Site(void) : _StringBuffer(16UL) { Initialize(); }

//______________________________________________________________________________
_Site::_Site(_String const &s ) : _StringBuffer(s.s_length) {
  Initialize ();
  (*this) << &s;
}

//______________________________________________________________________________
_Site::_Site(char s) : _StringBuffer(16UL) {
  Initialize();
  (*this) << s;
}

//______________________________________________________________________________
_Site::_Site(long s) {
  this->SetRefNo(s);
}

  //______________________________________________________________________________
void _Site::Initialize(bool mem) {
  ref_no = HY_SITE_NULL_REFERENCE;
}

//______________________________________________________________________________
_Site::~_Site(void) {}

//______________________________________________________________________________
void _Site::Complete(void) {
  ref_no = ref_no < 0L ? -ref_no : ref_no;
}

//______________________________________________________________________________
void _Site::Clone (_Site const & source_object) {
  this->Clear();
  _StringBuffer::Clone(source_object);
  ref_no = HY_SITE_NULL_REFERENCE;
}

  //______________________________________________________________________________
void _Site::Duplicate (BaseRefConst source_object) {
  Clone (*(_Site*)source_object);
}

//______________________________________________________________________________
// It isn't immediately obvious that resetting the ref_no is necessary, but
// it seems like it would be the expected behaviour
void _Site::Clear(void) {
  this->_StringBuffer::Clear();
  this->_StringBuffer::Initialize();
  this->Initialize();
}

