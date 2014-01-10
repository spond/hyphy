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

#ifndef _HY_LIST_NUMERIC_
#define _HY_LIST_NUMERIC_
//#pragma once
#include "hy_list_orderable.h"

/*
  
  A resizable list which stores PAYLOAD types
  
  assumes that PAYLOAD understands the equal (==), assign (=), 
  and stack copy operations, as well as all ordering operations 
  (<,>,<=,>=), the addition/subtraction operation, and can be 
  cast to from _HY_LIST_NUMERIC_INVALID_VALUE_ and 0L

*/ 

#define _HY_LIST_NUMERIC_INVALID_VALUE_ 0L


template <typename PAYLOAD>
class _hyListNumeric : public _hyListOrderable<PAYLOAD> {
  public:
  
      // arithmetic series populator: size, first item, step
      _hyListNumeric(const unsigned long, const PAYLOAD, const PAYLOAD);


      /**
      * Populate a _hyListNumeric with integers incrementally.
      * Example: sl.Populate(4, 1, 2) = [1, 3, 5, 7]
      * @param s The substring to find
      * @param startat The index to start searching from
      * @param increment by Pass true for a case sensitive search
      * @return Nothing. Acts on the List object it was called from.
      */
      void Populate(const unsigned long, const PAYLOAD, const PAYLOAD);


      /* instead of throwing an error, returns the missing value */
      virtual PAYLOAD Element(const long);

      /**
      * SLKP: 20090508
      * Return the sum of all values in the list
      * Example: _SimpleList([4, 1, 2]).Sum() = 7
      * @return the sum of all values in the list
      */
      PAYLOAD Sum(void) const;


      /**
      * Add a value to each entry in the array
      * Example: _hyListNumeric(1,3,5,7).Offset(2) = [3, 5, 7, 9]
      * @param shift Value to add
      * @return Nothing. Acts on the List object it was called from.
      */
      void Offset(const PAYLOAD);
      
      /**
      * Convert (a sorted) list into a partition string for consumption by datafilters etc
      * Example: _hyListNumeric(1,2,3,7,8,9,10).ListToPartitionString() = "1-3,7-10"
      * @return The partition string
      */
      _String* ListToPartitionString(void) const;


      /**
      * SLKP: 20090508
      * Implements a counting sort procedure, ASSUMING that all
      * list values are in [0, upperBound-1]; if the 1st argument is _HY_LIST_NUMERIC_INVALID_VALUE_, it is
      * automatically determined. This only really makes sense for integer types
      * @return a pointer to the sorted list
      * if the second argument is not nil, then
      * the new_order->old_order mapping is returned in the array pointed to
      *
      */
      
      _hyListNumeric <PAYLOAD> *CountingSort(PAYLOAD, _hyListNumeric <long> * = nil);

      virtual BaseRef toStr();

};

#include "hy_list_numeric.cpp"

#endif
