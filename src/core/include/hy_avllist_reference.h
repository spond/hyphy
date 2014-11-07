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

#ifndef _AVLLISTBASE_
#define _AVLLISTBASE_
//#pragma once

#include <hy_avllistbase.h>
#include <hy_list_reference_orderable.h>


/**
 * This object implements a set functionality using
 * a balanced binary search tree.
*/


//_____________________________________________________________________________
template <typename KEYTYPE>
class _AVLListReference : public virtual _AVLListBase<KEYTYPE*>{
  
protected:
  
  /**
   * This list stores the keys present in the list
   * they are tied to tre tree nodes by index, i.e. the key stored in the i-th index
   */
  
   _hyListReferenceOrderable    <KEYTYPE>        keys;
    virtual long _CompareIndexToValue (long node, KEYTYPE * const & key) const ;
  
  
  /**
   * Stores a key in the list at a given index
   * Must be implemented by a derived class
   * @param key The key to store (assumed to NOT already be in the tree, otherwise things will break)
   * @param index The index to store at (pass HY_LIST_INSERT_AT_END to find an unused index to store)
   * @return -1 if keys[node] < key , 0 if keys[node] == key, or 1 if keys[node] > key
   */
  
   virtual long _StoreKey   ( KEYTYPE * const & key, long index = HY_LIST_INSERT_AT_END);
  
  /**
   * Remove the key from 'index' (note that the tree structure is handled by the ::Delete function)
   * @param index The index to delete from (assumed to be valid)
   */
  virtual void _RemoveKey   (long index);
  virtual KEYTYPE* const * _AtIndex (const unsigned long) const;
  
  
public:
  
  
  /**
   * Construct an empty AVLList
   */
  
  _AVLListReference     (void);
  
  /**
   * Stack copy constructor
   */
  
  _AVLListReference     (_AVLListReference <KEYTYPE> const & );

  /**
   * Single item constructor; no counter reference incrementing is performed.
   * @sa InsertReference
   */
  
  _AVLListReference     ( KEYTYPE & );
  
  /**
   * Single item constructor; counter reference incrementing is performed.
   * @sa InsertReference
   */
  
  _AVLListReference     ( KEYTYPE * );

  /**
   * List of items constructor
   */
  
  _AVLListReference     (_hyListReference <KEYTYPE> const &);

  
  /**
   * Object destuctor
   */
  
  virtual ~_AVLListReference(void);
  
  /**
   * Initialize a freshly created object
   */
  void Initialize (bool = false);
  
  /**
   * Compare two lists for equality (i.e. do they represent the same set of keys)
   * @param rhs The _AVLListReference to copy from
    */
  virtual const _AVLListReference<KEYTYPE>& operator = (_AVLListReference <KEYTYPE> const & rhs);

  /**
   * Clone an existing object into this object, which has been previously initilized
   * @param source the object to clone from
   */
  void Clone (_AVLListReference <KEYTYPE> const & source);

  /* Insert a key (which is a reference) and add a reference to the reference counter
   * @param key the key to insert
   * @return (same as Insert); the index of the slot where the object was insterted
   * @sa Insert
   */
  
  virtual long InsertReference  (KEYTYPE& key);

  
  virtual BaseRef DeepCopy (void) const;
  virtual void Duplicate(BaseObj const * ref);
  
  
  
};

//#include "hy_avllist.cpp"

//*************** CONSTRUCTORS ***************//


template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::_AVLListReference(void):_AVLListBase<KEYTYPE*> () {
  this->Initialize();
}

template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::_AVLListReference(_AVLListReference<KEYTYPE> const & source):_AVLListBase<KEYTYPE*> (source) {
  this->Clone (source);
}

template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::_AVLListReference(KEYTYPE & item) {
  this->Initialize();
  this->Insert (&item);
}

template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::_AVLListReference(KEYTYPE * item) {
  this->Initialize();
  this->InsertReference (*item);
}

template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::_AVLListReference(_hyListReference<KEYTYPE> const & items) {
  this->Initialize();
  for (unsigned long k = 0UL; k < items.Length(); k+=1) {
    this->InsertReference (*items(k));
  }
}


//*************** INITIALIZER and CLONER ***************//
template <typename KEYTYPE>
void _AVLListReference<KEYTYPE>::Clone(_AVLListReference<KEYTYPE> const & source) {
  this->keys.Clear();
  this->_AVLListBase<KEYTYPE*>::Clone (source);
  this->keys.Clone (source.keys); // this should break, eh?
}

template <typename KEYTYPE>
void _AVLListReference<KEYTYPE>::Initialize(bool) {
}


//*************** DESTRUCTOR ***************//

template <typename KEYTYPE>
_AVLListReference<KEYTYPE>::~_AVLListReference(void) {
}

//*************** ASSIGNMENT OPERATOR ***************//

template <typename KEYTYPE>
const _AVLListReference<KEYTYPE>& _AVLListReference<KEYTYPE>::operator = (_AVLListReference<KEYTYPE> const & rhs) {
  this->Clone (rhs);
  return *this;
}



//*************** REQUIRED FUNCTION DEFINITIONS ***************//

template <typename KEYTYPE>
long _AVLListReference<KEYTYPE>::_CompareIndexToValue(long node, KEYTYPE * const & key ) const {
  return -this->keys.CompareToValue (node, key);
}

template <typename KEYTYPE>
long _AVLListReference<KEYTYPE>::_StoreKey( KEYTYPE * const & key, long index) {
  index = this->_AVLListBase <KEYTYPE*>::_StoreKey (key, index);
  this->keys.append_or_insert (key, index);
  return index;
}

template <typename KEYTYPE>
void _AVLListReference<KEYTYPE>::_RemoveKey(long index) {
  BaseObj::DeleteObject(this->keys.AtIndex (index));
  this->keys.SetItem (index, NULL);
  this->_AVLListBase <KEYTYPE*>::_RemoveKey (index);
}

template <typename KEYTYPE>
KEYTYPE * const * _AVLListReference<KEYTYPE>::_AtIndex(unsigned long index) const {
  return & keys.AtIndex (index);
}

template <typename KEYTYPE>
BaseObj* _AVLListReference<KEYTYPE>::DeepCopy (void) const {
  return new _AVLListReference <KEYTYPE> (*this);
}

template <typename KEYTYPE>
void _AVLListReference<KEYTYPE>::Duplicate (BaseObj const * ref) {
  this->Clone (*dynamic_cast<_AVLListReference<KEYTYPE> const *> (ref));
}

template <typename KEYTYPE>
long _AVLListReference<KEYTYPE>::InsertReference(KEYTYPE & item) {
  long inserted_here = this->Insert(& item);
  if (inserted_here >= 0) {
    item.AddAReference();
  }
  return inserted_here;
}



#endif
