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

#ifndef _HY_DICTIONARY_
#define _HY_DICTIONARY_
//#pragma once
#include <hy_avllist.h>


/**
 * This object implements a key:value dictionary functionality using
 * a balanced binary search tree.
 * @param KEYTYPE is the type used to represent keys; it must support stack copy, all pairwise comparison operations, i.e. ==, <= etc
 * @param PAYLOAD is the type which represents dictionary values; it must support stack copy and assignment (very little else is assumed)
 */

template <typename KEYTYPE, typename PAYLOAD>
struct _DictionaryHelper {
  KEYTYPE key;
  PAYLOAD value;
  
  bool operator == (_DictionaryHelper <KEYTYPE, PAYLOAD> const & rhs) const {
    return key == rhs.key;
  }
  bool operator < (_DictionaryHelper <KEYTYPE, PAYLOAD> const & rhs) const {
    return key < rhs.key;
  }
  bool operator > (_DictionaryHelper <KEYTYPE, PAYLOAD> const & rhs) const {
    return key > rhs.key;
  }
  bool operator <= (_DictionaryHelper <KEYTYPE, PAYLOAD> const & rhs) const {
    return key <= rhs.key;
  }
  bool operator >= (_DictionaryHelper <KEYTYPE, PAYLOAD> const & rhs) const {
    return key >= rhs.key;
  }
  
};


//_____________________________________________________________________________
template <typename KEYTYPE, typename PAYLOAD>
class _Dictionary : public virtual _AVLList<_DictionaryHelper<KEYTYPE, PAYLOAD> >{
  
protected:
  
  const _DictionaryHelper<KEYTYPE, PAYLOAD> munger (KEYTYPE const& k, PAYLOAD const & v) {
    _DictionaryHelper<KEYTYPE, PAYLOAD> combo_key;
    combo_key.key = k;
    combo_key.value = v;
    return combo_key;
  }
  
public:
  
  /**
   * Stack copy constructor
   */
  
  _Dictionary     () {};

  _Dictionary     (_Dictionary <KEYTYPE, PAYLOAD> const & );

  /**
   * Single item constructor
   */
  
  _Dictionary     (KEYTYPE const &, PAYLOAD const&);
  
  /**
   * List of items constructor
   */
  
  _Dictionary     (_hyList <KEYTYPE> const &, _hyList <PAYLOAD> const &);

  

  
  long InsertPair  (KEYTYPE const& key, PAYLOAD const & value);
  virtual PAYLOAD const *  Retrieve (KEYTYPE const& key) const;
  long   FindKey (const KEYTYPE& key, _AVLListTraversalHistory * history = NULL) const;
  
};


//*************** CONSTRUCTORS ***************//



template <typename KEYTYPE, typename PAYLOAD>
_Dictionary<KEYTYPE, PAYLOAD>::_Dictionary(_Dictionary<KEYTYPE, PAYLOAD> const & source):_AVLList<KEYTYPE> (source) {
  this->_AVLList<_DictionaryHelper<KEYTYPE, PAYLOAD> >::Clone (source);
}

template <typename KEYTYPE, typename PAYLOAD>
_Dictionary<KEYTYPE, PAYLOAD>::_Dictionary (KEYTYPE const & key, PAYLOAD const & value) {
  this->InsertPair (key, value);
}

template <typename KEYTYPE, typename PAYLOAD>
_Dictionary<KEYTYPE, PAYLOAD>::_Dictionary(_hyList<KEYTYPE> const & keys, _hyList<PAYLOAD> const & values) {
  for (unsigned long k = 0UL; k < keys.Length() && k < values.Length(); k+=1) {
    this->InsertPair (keys.AtIndex (k), values.AtIndex(k));
  }
}

//*************** ACCESS and RETRIVEAL FUNCTIONS ***************//

template <typename KEYTYPE, typename PAYLOAD>
long _Dictionary<KEYTYPE, PAYLOAD>::FindKey (KEYTYPE const & key, _AVLListTraversalHistory * history) const {
  _DictionaryHelper <KEYTYPE, PAYLOAD> dict_key;
  dict_key.key = key;
  return   this->_AVLList<_DictionaryHelper<KEYTYPE, PAYLOAD> >::Find (dict_key, history);
}

template <typename KEYTYPE, typename PAYLOAD>
long _Dictionary<KEYTYPE, PAYLOAD>::InsertPair (KEYTYPE const & key, PAYLOAD const & value) {
  return   this->Insert (this->munger (key, value));
}

template <typename KEYTYPE, typename PAYLOAD>
 PAYLOAD const * _Dictionary<KEYTYPE, PAYLOAD>::Retrieve (KEYTYPE const & key) const {
   long item_location = this->FindKey (key);
   return item_location == HY_NOT_FOUND ? NULL : & this->_AtIndex (item_location)->value;
}
#endif
