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
 ==============================================================
 Constructors
 ==============================================================
 */ // Does nothing
template<typename PAYLOAD>
_hyListOrderable<PAYLOAD>::_hyListOrderable() {
}

  //Data constructor (1 member list)
template<typename PAYLOAD>
_hyListOrderable<PAYLOAD>::_hyListOrderable(const PAYLOAD item) : _hyList<PAYLOAD> (item) {
}


  //Stack copy contructor
template<typename PAYLOAD>
_hyListOrderable<PAYLOAD>::_hyListOrderable(const _hyListOrderable <PAYLOAD> &l, const long from, const long to) 
                         : _hyList <PAYLOAD> (l, from, to) {
}

  // Data constructor (variable number of long constants)
template<typename PAYLOAD>
_hyListOrderable<PAYLOAD>::_hyListOrderable(const unsigned long number, const PAYLOAD items[]) : 
_hyList<PAYLOAD> (number, items) {
}

/*
==============================================================
Search/Insert Functions
==============================================================
*/

template<typename PAYLOAD>
long _hyListOrderable<PAYLOAD>::BinaryFind(const PAYLOAD item, const long startAt) const {

  
  long top = this->lLength - 1L,
       bottom = startAt,
       middle;

  if (top == -1L) {
    return -2L;
  }

  while (top > bottom) {
    middle = (top + bottom) >> 1;
    if (CompareToValue (middle, item) == HY_COMPARE_GREATER) {
      top = middle == top ? top - 1L : middle;
    } else if (CompareToValue (middle, item) == HY_COMPARE_LESS) {
      bottom = middle == bottom ? bottom + 1 : middle;
    } else {
      return middle;
    }
  }

  middle = top;
  if (this->ItemEqualToValue (middle,item)) {
    return middle;
  } else {
    if (CompareToValue(middle,item) == HY_COMPARE_LESS) {
      return -middle - 3;
    }
  }

  return -middle - 2;
}

template<typename PAYLOAD>
long _hyListOrderable<PAYLOAD>::BinaryInsert(const PAYLOAD item) {
  if (this->lLength == 0UL) {
    this->append (item);
    return 0L;
  }

  long pos = -BinaryFind(item) - 2L;

  if (pos < 0L) {
    return -pos - 2L;
  }

  if (pos < this->lLength && CompareToValue (pos,item) == HY_COMPARE_LESS) {
    pos++;
  }
  
  this->InsertElement(item, pos);

  return pos >= this->lLength ? this->lLength - 1UL : pos;
}


/*
==============================================================
Summary Functions 
==============================================================
*/

template<typename PAYLOAD>
PAYLOAD _hyListOrderable<PAYLOAD>::Max(void) const{
  PAYLOAD res = this->lData[0];
  for (unsigned long e = 1UL; e < this->lLength; e++)
    if (CompareToValue (e, res) == HY_COMPARE_GREATER) {
      res = this->lData[e];
    }
  return res;
}

template<typename PAYLOAD>
PAYLOAD _hyListOrderable<PAYLOAD>::Min(void) const{
  PAYLOAD res = this->lData[0];
  for (unsigned long e = 1UL; e < this->lLength; e++)
    if (CompareToValue (e, res) == HY_COMPARE_LESS) {
      res = this->lData[e];
    }
  return res;
}




/*
==============================================================
Sorting Functions 
==============================================================
*/


template<typename PAYLOAD>
bool _hyListOrderable<PAYLOAD>::IsSorted (void) const {
  
  for (unsigned long i = 0UL; 1UL + i < this->countitems(); i++) {
    if (this->Compare (i, i+1) == HY_COMPARE_GREATER) {
      return false;
    }
  }
  
  return true;
}

template<typename PAYLOAD>
long _hyListOrderable<PAYLOAD>::Compare(const long i, const long j) const {
  /*
  if (i < 0 || j < 0 || i > (long)this->lLength || j > (long)this->lLength) {
    printf ("Comparing out of bounds %ld %ld %ld\n", i, j, this->lLength);
  }
  */
  if (this->lData[i] < this->lData[j]) {
    return HY_COMPARE_LESS;
  } else if (this->lData[i] == this->lData[j]) {
    return HY_COMPARE_EQUAL;
  }
  return HY_COMPARE_GREATER;
}

template<typename PAYLOAD>
long _hyListOrderable<PAYLOAD>::CompareToValue(const long item, const PAYLOAD& value) const {
  
  if (this->lData[item] < value) {
    return HY_COMPARE_LESS;
  } else if (this->lData[item] > value) {
    return HY_COMPARE_GREATER;
  }
  return HY_COMPARE_EQUAL;
}


template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::BubbleSort(_hyListOrderable <long> * index_list) {
  bool done = false;
  while (!done) {
    done = true;
    for (unsigned long i = 0UL, j = i + 1UL; i + 1UL < this->countitems(); i++, j++) {
      if (this->Compare(i, j) == HY_COMPARE_GREATER) {
        done = false;
        this->Swap (i,j);
        if (index_list) {
          index_list->Swap (i,j);
        }
      }
    }
  }
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::QuickSort(const unsigned long from, const unsigned long to, _hyListOrderable <long> * index_list) {

  if (from >= to || from >= this->countitems()) {
    return;
  } 
  if (to >= this->countitems() && from < this->countitems()) {
     this->QuickSort (from, this->countitems() - 1, index_list); 
     return;
  }

  unsigned long middle = (from + to) >> 1, 
                top = to,
                bottommove = 1UL, 
                topmove = 1UL;
                
  long          imiddleV = index_list?index_list->AtIndex(middle):0L;
         
  PAYLOAD middleV = this->AtIndex(middle);
  
  if (middle) {
    while (middle >= from + bottommove &&
           this->Compare(middle - bottommove, middle) == HY_COMPARE_GREATER) {
      bottommove++;
    }
  }

  if (from < to) {
    while (middle + topmove <= to &&
           this->Compare(middle + topmove, middle) == HY_COMPARE_LESS) {
      topmove++;
    }
  }
  
  // now shuffle
  for (unsigned long i = from; i + bottommove < middle; i++) {
    if (this->Compare(i, middle) == HY_COMPARE_GREATER) {
      this->Swap (i, middle-bottommove);
      if (index_list) {
        index_list->Swap (i, middle-bottommove);
      }
      bottommove++;

      while (middle >= from + bottommove &&
             Compare(middle - bottommove, middle) == HY_COMPARE_GREATER) {
        bottommove++;
      }
    }
  }

  for (unsigned long i = middle + topmove + 1; i <= top; i++) {
    if (Compare(i, middle) == HY_COMPARE_LESS) {
      this->Swap (i, middle+topmove);
      if (index_list) {
        index_list->Swap (i,middle+topmove);
      }
      topmove++;

      while (middle + topmove <= to &&
             Compare(middle + topmove, middle) == HY_COMPARE_LESS) {
        topmove++;
      }
    }
  }

  if (topmove == bottommove) {
    for (unsigned long i = 1UL; i < bottommove; i++) {
      this->Swap (middle + i, middle -i);
      if (index_list) {
        index_list->Swap (middle + i, middle -i);
      }
    }
  } else if (topmove > bottommove) {
    unsigned long shift = topmove - bottommove;
    for (unsigned long i = 1UL; i < bottommove; i++) {
      this->Swap (middle-i, middle+i+shift);
      if (index_list) {
        index_list->Swap (middle-i, middle+i+shift);
      }
    }
    for (unsigned long i = 0UL; i < shift; i++) {
      this->lData[middle+i] = this->lData[middle+i+1];
      if (index_list) {
        (*index_list)[middle+i] = index_list->AtIndex(middle+i+1);
      }
    }
    middle += shift;
    this->lData[middle] = middleV;
    if (index_list) {
      (*index_list)[middle] = imiddleV;
    }
  } else {
    unsigned long shift = bottommove - topmove;
    for (unsigned long i = 1UL; i < topmove; i++) {
      this->Swap (middle+i, middle-i-shift);
      if (index_list) {
        index_list->Swap (middle+i, middle-i-shift);
      }
    }
    for (unsigned long i = 0UL; i < shift; i++) {
      this->lData[middle-i] = this->lData[middle-i-1];
      if (index_list) {
        (*index_list)[middle-i] = index_list->AtIndex(middle-i-1);
      }
    }
    middle -= shift;
    this->lData[middle] = middleV;
    if (index_list) {
      (*index_list)[middle] = imiddleV;
    }
  }
  if (to > middle + 1) {
    QuickSort(middle + 1, top, index_list);
  }
  if (from + 1 < middle) {
    QuickSort(from, middle - 1,index_list);
  }
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::Sort(bool ascending, _hyListOrderable <long> * index_list) {
  if (this->countitems() < 10UL) { 
    this->BubbleSort(index_list);
  } else {
    this->QuickSort(0, this->lLength - 1, index_list);
  }

  if (!ascending) {
    this->Flip();
    if (index_list) {
      index_list->Flip();
    }
  }
}

/*
==============================================================
Set Operations
==============================================================
*/

//Delete duplicates from a sorted list
template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::DeleteDuplicates(void) {
  if (this->lLength > 1) {
    _hyListOrderable <PAYLOAD> noDups;

    PAYLOAD lastValue = this->lData[0];
    noDups << lastValue;
    
    for (unsigned long k = 1; k < this->lLength; k++) {
      PAYLOAD thisValue = this->lData[k];
      if (!this->ItemEqualToValue (k,lastValue)) {
        noDups << thisValue;
        lastValue = thisValue;
      }
    }

    if (noDups.lLength < this->lLength) {
      this->Clone(noDups);
    }
  }
}

template<typename PAYLOAD>
long _hyListOrderable<PAYLOAD>::CountCommonElements(const _hyListOrderable &l1, bool at_least_one) const {
  unsigned long c1 = 0UL, c2 = 0UL, res = 0L;

  while (c1 < l1.lLength && c2 < this->lLength) {
    while (l1.CompareToValue (c1,this->lData[c2]) == HY_COMPARE_LESS) {
      c1++;
      if (c1 == l1.lLength) {
        break;
      }
    }
    if (c1 == l1.lLength) {
      break;
    }
    
    while (l1.CompareToValue (c1, this->lData[c2]) == HY_COMPARE_EQUAL) {
      c2++;
      if (at_least_one) {
        return 1;
      } else {
        res++;
      }
      if (c1 == l1.lLength || c2 == this->lLength) {
        break;
      }
    }
    if (c1 == l1.lLength || c2 == this->lLength) {
      break;
    }
    while (CompareToValue (c2, l1.lData[c1]) == HY_COMPARE_LESS) {
      c2++;
      if (c2 == this->lLength) {
        break;
      }
    }
  }
  return res;
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::FilterRange(const PAYLOAD lb, const PAYLOAD ub) {
  if (ub <= lb) {
    this->Clear();
  } else {
    _hyListOrderable <long> toDelete;
    for (unsigned long k = 0UL; k < this->lLength; k++)
      if (CompareToValue (k,lb) != HY_COMPARE_GREATER || CompareToValue (k,ub) != HY_COMPARE_LESS) {
        toDelete << k;
      }
    this->DeleteList(&toDelete);
  }
}

template<typename PAYLOAD>
_hyListOrderable<PAYLOAD> _hyListOrderable<PAYLOAD>::operator + (const _hyListOrderable <PAYLOAD> & l1) {
  _hyListOrderable result;
  result.Union (this, &l1);
  return result;
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::Union(const _hyListOrderable <PAYLOAD> * l1,const _hyListOrderable <PAYLOAD> * l2) {
  this->Clear();

  unsigned long nt1 = l1->countitems(),
                nt2 = l2->countitems(),
                c1 = 0UL,
                c2 = 0UL;

  while (c1 < nt1 && c2 < nt2) {
    while (l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_LESS) {
      (*this) << l1->AtIndex(c1++);
      if (c1 == nt1) {
        break;
      }
    }

    if (c1 == nt1) {
      break;
    }

    while (l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_EQUAL) {
      (*this) << l1->AtIndex(c1++);
      c2++;
      if (c1 == nt1 || c2 == nt2) {
        break;
      }
    }

    if (c1 == nt1 || c2 == nt2) {
      break;
    }

    while (l2->CompareToValue (c2, l1->AtIndex(c1)) == HY_COMPARE_LESS) {
      (*this) << l2->AtIndex(c2++);
      if (c2 == nt2) {
        break;
      }
    }
  }

  while (c1 < nt1) {
    (*this) << l1->AtIndex(c1++);
  }
  while (c2 < nt2) {
    (*this) << l2->AtIndex(c2++);
  }

}

template<typename PAYLOAD>
_hyListOrderable<PAYLOAD> _hyListOrderable<PAYLOAD>::operator % (const _hyListOrderable <PAYLOAD> & l1) {
  _hyListOrderable result;
  result.XOR (this, &l1);
  return result;
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::XOR(const _hyListOrderable <PAYLOAD> * l1,const _hyListOrderable <PAYLOAD> * l2) {
  this->Clear();

  unsigned long nt1 = l1->countitems(),
                nt2 = l2->countitems(),
                c1 = 0UL, 
                c2 = 0UL;

  while (c1 < nt1 && c2 < nt2) {
    while (c1 < nt1 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_LESS) {
      (*this) << l1->AtIndex(c1++);
    }
    if (c1 == nt1) {
      break;
    }
    while (c1 < nt1 && c2 < nt2 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_EQUAL) {
      c1++;
      c2++;
    }
    if (c1 == nt1 || c2 == nt2) {
      break;
    }

    while (c2 < nt2 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_GREATER) {
      (*this) << l2->AtIndex(c2++);
    }
  }

  while (c1 < nt1) {
    (*this) << l1->AtIndex(c1++);
  }
  while (c2 < nt2) {
    (*this) << l2->AtIndex(c2++);
  }
}

template<typename PAYLOAD>
_hyListOrderable<PAYLOAD> _hyListOrderable<PAYLOAD>::operator * (const _hyListOrderable <PAYLOAD> & l1) {
  _hyListOrderable result;
  result.Intersect (this, &l1);
  return result;
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::Intersect(const _hyListOrderable <PAYLOAD>* l1,const _hyListOrderable <PAYLOAD>* l2) {
  this->Clear();

  unsigned long nt1 = l1->countitems(),
                nt2 = l2->countitems(),
                c1 = 0UL, 
                c2 = 0UL;

  while (c1 < nt1 && c2 < nt2) {
    while (l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_LESS) {
      c1++;
      if (c1 == nt1) {
        break;
      }
    }
    if (c1 == nt1) {
      break;
    }

    while (l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_EQUAL) {
      (*this) << l1->AtIndex(c1++);
      c2++;
      if (c1 == nt1 || c2 == nt2) {
        break;
      }
    }
    if (c1 == nt1 || c2 == nt2) {
      break;
    }
    while (l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_GREATER) {
      c2++;
      if (c2 == nt2) {
        break;
      }
    }
  }
}

template<typename PAYLOAD>
_hyListOrderable<PAYLOAD> _hyListOrderable<PAYLOAD>::operator - (const _hyListOrderable <PAYLOAD> & l1) {
  _hyListOrderable result;
  result.Subtract (this, &l1);
  return result;
}

template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::Subtract(const _hyListOrderable <PAYLOAD> * l1,const _hyListOrderable <PAYLOAD> * l2) {
  this->Clear();

  unsigned long nt1 = l1->countitems(),
                nt2 = l2->countitems(),
                c1 = 0UL, 
                c2 = 0UL;

  while (c1 < nt1 && c2 < nt2) {
    while (c1 < nt1 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_LESS) {
      (*this) << l1->AtIndex(c1++);
    }
    if (c1 == nt1) {
      break;
    }
    
    while (c1 < nt1 && c2 < nt2 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_EQUAL) {
      c1++;
      c2++;
    }
    if (c1 == nt1 || c2 == nt2) {
      break;
    }
    while (c2 < nt2 && l1->CompareToValue (c1, l2->AtIndex (c2)) == HY_COMPARE_GREATER) {
      c2++;
    }
  }

  while (c1 < nt1) {
    (*this) << l1->AtIndex(c1++);
  }
}

template<typename PAYLOAD>
_hyListOrderable<PAYLOAD> _hyListOrderable<PAYLOAD>::operator && (const _hyListOrderable <PAYLOAD> & l1) {
  _hyListOrderable result;
  result.Merge (this, &l1);
  return result;
}


template<typename PAYLOAD>
void _hyListOrderable<PAYLOAD>::Merge(const _hyListOrderable <PAYLOAD> *l1, const _hyListOrderable <PAYLOAD> *l2, 
  _hyListOrderable <long> *mergeResults1, _hyListOrderable <long> *mergeResults2)
{
  this->Clear();
  if (mergeResults1) {
    mergeResults1->Clear();
  }
  if (mergeResults2) {
    mergeResults2->Clear();
  }
  
  enum    machine_states {INIT, ADVANCE1, ADVANCE2, FLUSH1, FLUSH2} advancing = INIT;

  unsigned long    pos1 = 0,
                   pos2 = 0,
                   nt1 = l1->countitems(),
                   nt2 = l2->countitems();
                   
  
  
  
  bool  keep_going = true;
  
  while (keep_going) { // stuff left to do
    //printf ("STATE %u, pos1 %lu/%lu, pos2 %lu/%lu / %lu\n", advancing, pos1, (unsigned long)l1->AtIndex(pos1), pos2, (unsigned long)l2->AtIndex(pos2), this->countitems());
    /*if (pos1 >= nt1 || pos2 >= nt2) {
      WarnError ("FUBAR!");
    }*/
    
    switch (advancing) {
    
      case ADVANCE1: { // advancing in the 1st list
        pos1++;
        if (pos1==nt1) {
          advancing = FLUSH2;
          continue;
        }

        long cmp = l1->CompareToValue (pos1,l2->AtIndex(pos2));
        //if (l1lData[pos1] <= l2->lData[pos2]) {
        if ( cmp != HY_COMPARE_GREATER) {
          if (mergeResults1) {
            //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
            (*mergeResults1)<<this->lLength;
          }
          
          this->append (l1->AtIndex(pos1));
            
  //        if (mergeResults2 && l1->lData[pos1] < l2->lData[pos2]) {
          if (cmp == HY_COMPARE_LESS) {
            if (mergeResults2 && mergeResults2->countitems () == 0UL && pos1 >= pos2) {
              for (unsigned long i=0UL; i<pos2; i++) {
                  mergeResults2->append (i);
              }
            }
            continue;
          }
        }
        
        if (cmp == HY_COMPARE_GREATER) {
        //if (l1->lData[pos1] > l2->lData[pos2]) {
          advancing = ADVANCE2;
          if (mergeResults1 && mergeResults1->countitems () == 0UL ) {
            for (unsigned long i=0UL; i<pos1; i++) {
              //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
              mergeResults1->append (i);
            }
          }
          
          if (mergeResults2) {
            (*mergeResults2)<<this->lLength;
          }
          
          //printf ("this->append (l2->AtIndex(pos2))\n");
          this->append (l2->AtIndex(pos2));
          continue;
        }
        break;
      } 
      
      case ADVANCE2: { // advancing in the 2nd list
        pos2++;
        if (pos2==nt2) {
          advancing = FLUSH1;
          continue;
        }
          
        long cmp = l2->CompareToValue (pos2,l1->AtIndex(pos1));

        //if (l2->lData[pos2] <= l1->lData[pos1]) {
        if (cmp != HY_COMPARE_GREATER) {
           if (mergeResults2) {
            (*mergeResults2)<<this->lLength;
          }
          
          this->append (l2->AtIndex(pos2));

          //if (l2->lData[pos2] < l1->lData[pos1] && mergeResults1 && !doMerge1 && pos2>=pos1) {
          if (cmp == HY_COMPARE_LESS ) {
           if(mergeResults1 && mergeResults1->countitems() == 0 && pos2>=pos1) {
              for (unsigned long i=0UL; i<pos1; i++) {
                //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
                (*mergeResults1)<<i;
              }
            }
            continue;
          }
        }
        
        //if (l2->lData[pos2] > l1->lData[pos1]) {
        if (cmp == HY_COMPARE_GREATER) { 
          advancing = ADVANCE1;
          if (mergeResults2 && mergeResults2->countitems() == 0) {
            for (unsigned long i=0UL; i<pos2; i++) {
              (*mergeResults2)<<i;
            }
          }
          if (mergeResults1) {
            //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
            (*mergeResults1)<<this->lLength;
          }
          this->append (l1->AtIndex(pos1));
          continue;
        }
        break;
      } 
      case FLUSH2: { // flush out the 2nd list
        if (mergeResults1 && pos2<nt2 ) {
          for (unsigned long i=pos1; i<nt1; i++) {
             //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
            (*mergeResults1)<<i;
          }
        }
        if (mergeResults2)
          while (pos2<nt2) {
            (*mergeResults2)<<this->lLength;
            this->append (l2->AtIndex(pos2++));
          }
        else
          while (pos2<nt2) {
            this->append (l2->AtIndex(pos2++));
          }
        keep_going = false;
        break;
      } 
      case FLUSH1: { // flush out the 1st list
        if (mergeResults2 && pos1<nt1) {
          for (unsigned long i=pos2; i<nt2; i++) {
            (*mergeResults2)<<i;
          }
        }
        if (mergeResults1)
          while (pos1<nt1) {
            //printf("MERGE line number %d in file %s\n", __LINE__, __FILE__);
            (*mergeResults1)<<this->lLength;
            this->append (l1->AtIndex(pos1++));
          }
        else
          while (pos1<nt1) {
            this->append (l1->AtIndex(pos1++));
          }
        keep_going = false;
        break;
      } 
      case INIT: { // just starting
        if (!nt1) { // first list is empty!
          advancing = FLUSH2;
          continue;
        }
        if (!nt2) { // second list is empty!
          advancing = FLUSH1;
          continue;
        }
        
        //if (l1->lData[pos1] <= l2->lData[pos2]) { // begin with the first list
        
        long cmp = l1->CompareToValue (pos1, l2->AtIndex(pos2));
        
        if (cmp != HY_COMPARE_GREATER) { // begin with the first list
          if (mergeResults1) {
            (*mergeResults1)<<this->lLength;
          }
          this->append (l1->AtIndex(0UL));
          advancing = ADVANCE1;
          if (cmp != HY_COMPARE_EQUAL) {
            continue;
          }
        } else {
          if (mergeResults2) {
            (*mergeResults2)<<this->lLength;
          }
          this->append (l2->AtIndex(0UL));
          advancing = ADVANCE2;
          continue;
        }
        break;
      }
    } // end SWITCH
    
    if (keep_going) {
      if (advancing == ADVANCE1) { // moving up in the second term
        pos1++;
        if (pos1==nt1) {
          pos2++;
          if (mergeResults2) {
            (*mergeResults2)<<this->lLength-1UL;
          }
          advancing = FLUSH2;
          continue;
        } else {
          advancing = ADVANCE2;
          if (mergeResults2) {
            (*mergeResults2)<<this->lLength-1UL;
          }
        }
      } else {
        pos2++;
        if (pos2==nt2) {
          pos1++;
          if (mergeResults1) {
            (*mergeResults1)<<this->lLength-1UL;
          }
          advancing = FLUSH1;
          continue;
        } else {
          advancing = ADVANCE1;
          if (mergeResults1) {
            (*mergeResults1)<<this->lLength-1UL;
          }
        }
      }
    }
  }
}


