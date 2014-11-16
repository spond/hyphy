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

#ifndef _SITE_
#define _SITE_

#define HY_SITE_NULL_REFERENCE (-1L)

#include "hy_string_buffer.h"

class _Site : public _StringBuffer {

public:

  /**
   * A constructor that creates a Site object with no content, placeholder
   * reference to -1, and is incomplete
   */
  _Site(void);

  /**
   * A constructor that creates a Site object with given content, placeholder
   * reference to -1, and is incomplete
   * @param s The given content of the site
   */
  _Site(_String const &);

  /**
   * A constructor that creates a Site object with given content, placeholder
   * reference to -1, and is incomplete
   * @param c The given content of the site
   */
  _Site(char);

  /**
   * A constructor that creates a Site object with no content, but a given
   * reference, and is incomplete
   * @param r The given reference to another site
   */
  _Site(long);

  /**
   * A destructor. Does nothing.
   */
  virtual ~_Site(void);

  /**
   * Mark this site as complete. Uses the sign of ref_no as a switch to do
   * so.
   */
  void Complete(void);

  /**
   * Duplicate another Site
   * @param b The Site to be duplicated. Calls StringBuffer::duplicate, also
   * copy ref_no
   */
  void Clone (_Site const & source_object);

  /**
   * Duplicate another Site
   * @param b The Site to be duplicated. Calls StringBuffer::duplicate, also
   * copy ref_no
   */
  virtual void Duplicate (BaseRefConst source_object);

  /**
   * Replace the StringBuffer of this site and reset the ref_no
   */
  virtual void Clear(void);

  /**
   * Return the reference held by this site
   */
  long GetRefNo(void) { return ref_no < 0L ? -ref_no - 2L : ref_no - 2L; }

  // Complete and IsComplete are never used, but they don't make sense as
  // implemented before refactoring, where complete is when ref_no is < 0. I
  // believe this because complete makes ref_no positive always.
  /**
   * Return whether or not the site has had its Complete() called
   */
  bool IsComplete(void) { return ref_no > 0L; }

  /**
   * Set the reference held by this site to another site
   * @param the reference number of another site
   */
  void SetRefNo(long r) { ref_no = -r - 2L; }

private:

  
  /**
   * Perform default constuctor initalizations
   */

  virtual void Initialize (bool mem = false);
  
  /**
   * if this site contains a reference to another one
   * if ref_no is negative, then shows whether the definition of this site
   * has been completed
   */
  long ref_no;

};

#endif
