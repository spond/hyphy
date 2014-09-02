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

#ifndef _HY_LIST_REFERENCE_
#define _HY_LIST_REFERENCE_

#include "hy_list.h"

/*
 
 A resizable list which stores PAYLOAD* types and tracks
 references
 
 PAYLOAD objects are assumed to derive from BaseObject and 
 implement the Compare and Equal operations (only if sorting 
 is needed)
 
 */

template <typename PAYLOAD>
class _hyListReference : public virtual _hyList <PAYLOAD*> {

public:

  /**
  * A constructor.
  * A simple constructor that does nothing
  */
  _hyListReference();


  /**
   * A _hyListReference constructor from a single item
   * The reference counter for the item will be incremented
   * @param item the element to add to the list
   */
  _hyListReference(PAYLOAD&);


  /**
   * A _hyListReference constructor from a single item
   * The reference counter for the item will NOT be incremented
   * @param item the element to add to the list
   */
  _hyListReference(PAYLOAD * const);
  
  /**
  * Stack copy contructor
  * @param l List to be copied
  * @param from Beginning index to copy from
  * @param to Last index to copy to
  */
  _hyListReference(const _hyListReference<PAYLOAD> &, const long = 0, const long = HY_LIST_INSERT_AT_END);
  
  /**
   * Make a copy of the argument into this object
   * (clear all existing content first)
   * +1 to all reference counters of objects in source
   * @param source
   */
  virtual     void Clone (const _hyListReference<PAYLOAD> & source);


  /**
   * Data constructor from a static list of PAYLOAD object pointers
   * @param const unsigned long the number of PAYLOAD arguments supplied
   * to the constructor in the second argument
   * @param const PAYLOAD: the static list of items to pass to the constructor
   */
  
  _hyListReference (const unsigned long, PAYLOAD * []);


  /**
   * Construct a list of substrings from the original string separated by char
   * ONLY SPECIALIZED FOR PAYLOAD == _String
   * \n\n \b Example: \code  list = _hyListReference<_String>(
   * _String("one,two,three"), ','); returns ['one','two','three']; \endcode
   * @param the_string The substring to be parsed, remember to cast it as a BaseRef
   * @param separator The separator for the string
   */
  
  //_hyListReference(const _String& the_string, const char separator);

  virtual ~_hyListReference (void);
  
  /**
   * Add a new reference to the list WITHOUT incrementing the reference counter
   * \n\n \b Example: \code  list.AppendNewInstance (new _String ("something"))
   * @param the_ref The reference to be added.
  */
  
  void AppendNewInstance (PAYLOAD * the_ref);
  
  /**
   * In addition to what the base class does, this also
   * removes one reference from each object and deletes them if ref_count <= 1
   * @param compact Free allocated memory if true
   */
  
  virtual void          Clear(bool = true);

  
  /**
   * The standard assignment operator
   * Note that list contents are not copied by value, but only have their
   * reference counters incremented
   * @param l Copy data from
   */
  const _hyListReference<PAYLOAD> operator=(const _hyListReference<PAYLOAD>&);

  /**
   * Add all the elements from the argument list to the current list
   * Note that list contents are not copied by value, but only have their
   * reference counters incremented
   * @param l Copy data from
   */
  const _hyListReference<PAYLOAD> operator&(const _hyListReference<PAYLOAD>&);

  /**
   * Add a dynamic copy of the argument to the end of the list
   * @param l Copy data from
   */
  const _hyListReference<PAYLOAD> operator&(const PAYLOAD *);

  /**
   * Append a reference to the argument to the end of the list
   * Increments the reference counter
   * @param item add this reference
   */
  virtual void operator<<(PAYLOAD*);

  /**
   * Append a reference to the dynamic copy of the argument
   * @param item add the reference to a copy of the object referenced
   */
  virtual void operator&&(const PAYLOAD*);

  /**
   * Create a _String from the argument buffer and append to the list
   * Only specialized for PAYLOAD == STRING
   * @param buffer make the string from this char *
   */
  //virtual void operator&&(const char*);

  /**
   * Append all references from the argument to the end of the current list
   * Increments the reference counter for each added reference
   * @param l add items from this list to the reference
   */
  virtual void operator<<(const _hyListReference<PAYLOAD>&);
  
  /**
   * Append all references from the argument to the end of the current list
   * Increments the reference counter for each added reference
   * @param l add items from this list to the reference
   */
  
  /**
   * Checks if list if list element at 'index' is equal to a fixed value
   * @param index the list index of the element to test
   * @param value the value to compare the result to
   * @return true if equal.
   */
  virtual bool ItemEqualToValue (unsigned long index,  PAYLOAD * const & value) const;
  
protected:

    /**
  * Stack copy contructor
  * @param l List to be copied
  * @param from Beginning index to copy from
  * @param to Last index to copy to
  */
  void AddReferenceToItems (long = 0, long = HY_LIST_INSERT_AT_END);

};

#include "hy_list_reference.cpp"

#endif

