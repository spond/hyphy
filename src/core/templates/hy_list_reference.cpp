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

/*
 Constructors
*/

template<typename PAYLOAD>
_hyListReference<PAYLOAD>::_hyListReference () : _hyList<PAYLOAD*> () {
}


template<typename PAYLOAD>
_hyListReference<PAYLOAD>::_hyListReference (PAYLOAD& value) : _hyList<PAYLOAD*> (&value) {
  value.AddAReference ();
}

template<typename PAYLOAD>
_hyListReference<PAYLOAD>::_hyListReference (PAYLOAD* const value) : _hyList<PAYLOAD*> (value) {
}

template<typename PAYLOAD>
_hyListReference<PAYLOAD>::_hyListReference (const _hyListReference<PAYLOAD> &l, const long from, const long to) : _hyList<PAYLOAD*> (l,from,to) {
    this->AddReferenceToItems ();
}

  // Data constructor (variable number of long constants)
template<typename PAYLOAD>
_hyListReference<PAYLOAD>::_hyListReference(const unsigned long number, PAYLOAD * items[]) : 
_hyList<PAYLOAD*> () {
  for (unsigned long k = 0; k < number; k ++) {
    (*this) << items[k];
  }
}


template<typename PAYLOAD>
_hyListReference<PAYLOAD>::~_hyListReference (void) {
  for (unsigned long k = 0; k < this->lLength; k++) {
    BaseObj::DeleteObject(this->lData[k]);
  }
}

/*
 Storage/reference managament functions
 */

template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::Clear (bool deallocate_memory) {
  for (unsigned long item = 0UL; item < this->lLength; item++) {
    BaseObj::DeleteObject(this->lData[item]);
  }
  this->_hyList<PAYLOAD*>::Clear(deallocate_memory);
}

template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::HandleItemDelete(const unsigned long index) const {
  printf ("_hyListReference<PAYLOAD>::HandleItemDelete\n");
  BaseObj::DeleteObject(this->lData[index]);
}

/*
 Accessor/storage functions
 */

template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::AppendNewInstance (PAYLOAD* the_ref) {
  this->append (the_ref);
}

template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::AddReferenceToItems (long from, long to) {
  NormalizeCoordinates(from, to, this->lLength);
  for (long index = from; index <= to; index++) {
    this->lData[index]->AddAReference();
  }
}

template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::Clone (const _hyListReference<PAYLOAD>& source) {
  this->_hyList<PAYLOAD*>::Clone (source);
  this->AddReferenceToItems();
}

/*
 Operator overloads
*/

  //Assignment operator
template<typename PAYLOAD>
_hyListReference<PAYLOAD> const _hyListReference<PAYLOAD>::operator=(const _hyListReference<PAYLOAD>& l)
{
   this->Clear (false);
   this->Clone (l);
   return *this;
}

  //Append a list
template<typename PAYLOAD>
_hyListReference<PAYLOAD> const _hyListReference<PAYLOAD>::operator&(const _hyListReference<PAYLOAD>& l)
{
  _hyListReference <PAYLOAD> res ;
  res.RequestSpace (this->lLength + l.lLength);
  res << (*this);
  res << l;
  return res;
}

  //Append a list
template<typename PAYLOAD>
_hyListReference<PAYLOAD> const _hyListReference<PAYLOAD>::operator&(const PAYLOAD* l)
{
  _hyListReference <PAYLOAD> res;
  res.RequestSpace (this->lLength + 1UL);
  
  res << (*this);
  res && l;
  return res;
}

  //append an element
template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::operator<<(PAYLOAD* item)
{
  this->append(item);
  item->AddAReference();
}

  //append the dynamic copy of item
template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::operator&&(const PAYLOAD* item)
{
   this->append (new PAYLOAD (*item));
}


  //append all elements in the list
template<typename PAYLOAD>
void _hyListReference<PAYLOAD>::operator<<(const _hyListReference<PAYLOAD>& l)
{
  this->RequestSpace (this->lLength + l.lLength);
  for (unsigned long k = 0UL; k < l.lLength; k++) {
    (*this) << l.lData[k];
  }
}

/*
 Element Comparison Functions
*/

template<typename PAYLOAD>
bool _hyListReference<PAYLOAD>::ItemEqualToValue(unsigned long index, PAYLOAD * const &  value) const {
    //printf ("_hyListReference::ItemEqualToValue\n");
  return this->lData[index]->Equal (*value);
}



