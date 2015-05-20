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

#include <iostream>
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Generate necessary includes from the respective implementation file
#include "hy_list_orderable.h"

namespace {

class _testOrderablePayload {
  public:
  
  _testOrderablePayload (void) { data [0] = 0; data [1] = 0;}
  _testOrderablePayload (unsigned long p) { data[0] = p; data[1] = p; }
  _testOrderablePayload (unsigned long p, unsigned long p2) { data[0] = p; data[1] = p2; }
  _testOrderablePayload (const _testOrderablePayload& o) { data[0] = o.data[1]; data[1] = o.data[1]; }
  
  bool operator == (const _testOrderablePayload & o) const { return data[0] == o.data[0] && data[1] == o.data[1];} 
  bool operator != (const _testOrderablePayload & o) const { return ! ((*this) == o);} 
  bool operator <  (const _testOrderablePayload & o) const { if (data[0] < o.data[0]) return true; if (data [0] == o.data[0]) {return data[1] < o.data[1];} return false;} 
  bool operator <= (const _testOrderablePayload & o) const { return (*this) < o || (*this == o); } 
  bool operator >  (const _testOrderablePayload & o) const { return  ! ((*this) <= o); } 
  bool operator >= (const _testOrderablePayload & o) const { return  ! ((*this) < o); } 
  operator unsigned long (void) {return data[0];}
  
  unsigned long data[2];
};

// The fixture for testing class Foo.
template <typename DATA>
class _hyListOrderableTest : public ::testing::Test {

protected:

  _hyListOrderableTest() {
    
  }

  virtual ~_hyListOrderableTest() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    
  }
  
  _hyListOrderable <DATA> make_random_list (const unsigned long size, const unsigned long range, const unsigned long offset = 0UL) {
    _hyListOrderable <DATA> random_list;
    for (unsigned long item = 0UL; item < size; item ++) {
      random_list.append ((DATA) (offset + genrand_int32() % range));
    }
    return random_list;
  }
  
  _StringBuffer dump_to_stream_as_longs (const _hyListOrderable<DATA>& data) {
    _StringBuffer result;
    char buffer [256];
    result << '[';
    for (unsigned long item = 0UL; item < data.countitems(); item++) {
      if (item) {
        result << ',';
      }
      snprintf(buffer,255,"%lu", (unsigned long)data.AtIndex (item));
      result << buffer;
    }
    result << ']';
    return result;
  } 

public:
  // Per-test-case set-up.
  // Called before the first test in this test case.
  // Can be omitted if not needed.
  static void SetUpTestCase() {
      //shared_resource_ = new ...;
  }

  // Per-test-case tear-down.
  // Called after the last test in this test case.
  // Can be omitted if not needed.
  static void TearDownTestCase() {
      // delete shared_resource_;
      // shared_resource_ = NULL;
  }

  
};

TYPED_TEST_CASE_P(_hyListOrderableTest);


TYPED_TEST_P (_hyListOrderableTest, ConstuctorTests) {
  
   TypeParam array [5] = {(TypeParam)1, (TypeParam)4, (TypeParam)9, (TypeParam)16, (TypeParam)25};
  
  _hyListOrderable <TypeParam> null_list,
                               single_element_list ((TypeParam)16),
                               multiple_element_list (5,array),
                               full_stack_copy (multiple_element_list),
                               partial_stack_copy (multiple_element_list,2,HY_LIST_INSERT_AT_END);
          
  ASSERT_EQ (0UL, null_list.countitems()) << "Non-empty null list";
  ASSERT_EQ (1UL, single_element_list.countitems()) << "Single element list has wrong length";
  ASSERT_EQ (5UL, multiple_element_list.countitems()) << "Array of elements list has wrong length";
  ASSERT_EQ (5UL, full_stack_copy.countitems()) << "Stack copy list has wrong length";
  ASSERT_EQ (3UL, partial_stack_copy.countitems()) << "Partial stack copy list has wrong length";
  
  EXPECT_EQ (single_element_list (0), full_stack_copy(3));   
  for (unsigned long i = 0UL; i < multiple_element_list.countitems(); i++) {
    EXPECT_EQ (full_stack_copy (i), full_stack_copy[i]);
  }
  
  EXPECT_TRUE(full_stack_copy == multiple_element_list) << "Failed list == list";
  EXPECT_FALSE(full_stack_copy == partial_stack_copy) << "Failed list != list";
  
  EXPECT_EQ (partial_stack_copy (0), multiple_element_list (2));
  EXPECT_EQ (partial_stack_copy (2), full_stack_copy (4));
  
  partial_stack_copy.Clear (false);
  EXPECT_EQ (0UL, partial_stack_copy.countitems());
  EXPECT_LT (0UL, partial_stack_copy.allocated());
  partial_stack_copy.Clear (true);
  EXPECT_EQ (0UL, partial_stack_copy.allocated());
}

TYPED_TEST_P (_hyListOrderableTest, SortingTests) {
  
   TypeParam array [6] = {(TypeParam)5, (TypeParam)2, (TypeParam)3, (TypeParam)2, (TypeParam)10, (TypeParam)1},
             array_sorted [6] = {(TypeParam)1, (TypeParam)2, (TypeParam)2, (TypeParam)3, (TypeParam)5, (TypeParam)10};
             
   long      direct_index [6] = {0L,1L,2L,3L,4L,5L};
             
   _hyListOrderable <TypeParam> unsorted      (6UL, array),
                                sorted        (6UL, array_sorted),
                                sort_me       (unsorted),
                                reverse_large,
                                direct_large, 
                                empty;
                                
   _hyListOrderable <long>      bubble_sort_indexer (6UL, direct_index),
                                quick_sort_indexer (6UL, direct_index);
                          
    // test some basic comparison operations 
    
    ASSERT_EQ (HY_COMPARE_LESS, sorted.Compare (0,4)) << "Failed a<b element comparison";
    ASSERT_EQ (HY_COMPARE_EQUAL, sorted.Compare (1,2)) << "Failed a==b element comparison";
    ASSERT_EQ (HY_COMPARE_GREATER, sorted.Compare (4,0)) << "Failed a>b element comparison";
    
    ASSERT_TRUE (sorted.IsSorted()) << "IsSorted returned false for a sorted list";
    ASSERT_FALSE (unsorted.IsSorted()) << "IsSorted returned true for an unsorted list";
    
    empty.Sort();
    ASSERT_TRUE (empty.IsSorted()) << "Empty list claimed to be unsorted";
    
    
    sort_me.BubbleSort (&bubble_sort_indexer);
    for (unsigned long i = 0UL; i < sort_me.countitems(); i++) {
      EXPECT_EQ (sorted (i), sort_me[i]) << "Bubble sort failed at element " << (i+1);
      EXPECT_EQ (unsorted (bubble_sort_indexer.AtIndex(i)), sort_me.AtIndex (i)) << "Sorted indices for bubble sort are incorrect at position " << i << " mapping to index " << bubble_sort_indexer.AtIndex(i);
    }
    sort_me.Clone (unsorted);
    sort_me.QuickSort (0, sort_me.countitems(), &quick_sort_indexer);
    for (unsigned long i = 0UL; i < sort_me.countitems(); i++) {
      EXPECT_EQ (sorted (i), sort_me[i]) << "Quick sort failed at element " << (i+1);
      EXPECT_EQ (unsorted (quick_sort_indexer.AtIndex(i)), sort_me.AtIndex (i)) << "Sorted indices for quick sort are incorrect at position " << i << " mapping to index " << quick_sort_indexer.AtIndex(i);
    }
    
    _hyListOrderable <long> index_list;
    
    for (unsigned long i = 0; i < 127; i++) {
      direct_large.append ((TypeParam)i);
      reverse_large.append ((TypeParam)(126-i));
      index_list.append (i);
    }
    
    _hyListOrderable <TypeParam> copy_reverse (reverse_large),
                                 copy_direct  (direct_large);
                                 
    copy_direct.Sort();
    ASSERT_EQ(copy_direct, direct_large) << "Sorting an already sorted list failed";
    reverse_large.QuickSort(0, reverse_large.countitems()-1, &index_list);
    for (unsigned long i = 0UL; i < copy_reverse.countitems(); i++) {
      EXPECT_EQ (direct_large.AtIndex(i), reverse_large.AtIndex(i)) << "Sort reverse list in ascending order at element " << (i+1);
      EXPECT_EQ (126-i, index_list.AtIndex(i)) << "Sorted index list is incorrect at element " << (i+1);
    }
    reverse_large.Sort(false, &index_list);
    ASSERT_EQ (reverse_large, copy_reverse) << "Sort reverse list in descending order failed";
    
    // random tests
    
    time_t timer;
    init_genrand (time(&timer));


    for (unsigned long iterations = 0UL; iterations < 1024UL; iterations ++) {
      _hyListOrderable <TypeParam> random_list (this->make_random_list (genrand_int32() % 512, 128));
      random_list.Sort();
      ASSERT_EQ(true,random_list.IsSorted()) << "Failed to sort a randomly generated list";
    }
    
}

TYPED_TEST_P (_hyListOrderableTest, InsertionAndSearchTests) {
  TypeParam array_sorted [6] = {(TypeParam)1, (TypeParam)2, (TypeParam)2, (TypeParam)3, (TypeParam)5, (TypeParam)10};
  
  
  _hyListOrderable <TypeParam> sorted        (6UL, array_sorted),
                               insertionTest (sorted);
  
  TypeParam ZERO = 0L,
            ONE  = 1L,
            FIVE = 5L,
            FOUR = 4L,
            ONE27 = 127L;
  
  /**** BINARY FIND ****/
  
  EXPECT_EQ (4L, sorted.BinaryFind (FIVE)) << "BinaryFind failed to correctly find 5 in the default list";
  EXPECT_EQ (0L, sorted.BinaryFind (ONE)) << "BinaryFind failed to correctly find 1 in the default list";
  EXPECT_EQ (-6L, sorted.BinaryFind (FOUR)) << "BinaryFind incorrectly found 4 in the default list";
  
  for (unsigned long iterations = 0UL; iterations < 1024UL; iterations ++) {
    _hyListOrderable <TypeParam> random_list (this->make_random_list (genrand_int32() % 512, 100));
    random_list.Sort();
    ASSERT_EQ(true,random_list.IsSorted()) << "Failed to sort a randomly generated list";
    if (random_list.countitems() > 0UL) {
      unsigned long item = genrand_int32() % random_list.countitems();
      ASSERT_EQ (random_list.AtIndex(item), random_list.AtIndex(random_list.BinaryFind (random_list.AtIndex (item))))
      << "An existing item in a random sorted list was not found by BinaryFind\n" 
      << this->dump_to_stream_as_longs (random_list).getStr();
    }
  }

  /**** BINARY INSERT ****/
  
  EXPECT_EQ (4L, sorted.BinaryInsert (FIVE)) << "BinaryInsert did not return the correct index for 5 in the default list";
  EXPECT_EQ (6UL, sorted.countitems ())      << "BinaryInsert inserted an already exsiting element into the default list";
  sorted.BinaryInsert (ZERO);
  ASSERT_EQ (true, sorted.IsSorted ()) << "BinaryInsert failed to maintain sortedness (inserting 0)"
   << this->dump_to_stream_as_longs (sorted).getStr();

  for (unsigned long iterations = 0UL; iterations < 1024UL; iterations ++) {
    _hyListOrderable <TypeParam> random_list (this->make_random_list (genrand_int32() % 64, 120,5));
    random_list.Sort();
    ASSERT_EQ(true,random_list.IsSorted()) << "Failed to sort a randomly generated list"  
        << this->dump_to_stream_as_longs (random_list).getStr();
    
    unsigned long previous_length = random_list.countitems();
    ASSERT_EQ (0L, random_list.BinaryInsert (ONE)) << "Element 1 was not inserted at the start of a random list";
    ASSERT_EQ(true,random_list.IsSorted()) << "Binary Insert did not preserve the sortedness of a list (inserting 1)"
        << this->dump_to_stream_as_longs (random_list).getStr();
    ASSERT_EQ (previous_length+1, random_list.BinaryInsert (ONE27)) << "Element 127 was not inserted at the end of a random list";
    ASSERT_EQ (previous_length+2, random_list.countitems()) << "The insertion of 1 and 127 did not increase the length of a random list by 2";
    ASSERT_EQ(true,random_list.IsSorted()) << "Binary Insert did not preserve the sortedness of a list (inserting 127)"  
        << this->dump_to_stream_as_longs (random_list).getStr();
  }
  
}

TYPED_TEST_P (_hyListOrderableTest, MinMaxTest) {
   TypeParam array [6] = {(TypeParam)10, (TypeParam)2, (TypeParam)3, (TypeParam)2, (TypeParam)5, (TypeParam)1},
             array_sorted [6] = {(TypeParam)1, (TypeParam)2, (TypeParam)2, (TypeParam)3, (TypeParam)5, (TypeParam)10};
                          
   _hyListOrderable <TypeParam> unsorted      (6UL, array),
                                sorted        (6UL, array_sorted);
  
    
   EXPECT_EQ (unsorted.AtIndex (5), unsorted.Min ()) << "Min failed on an unsorted list";
   EXPECT_EQ (sorted.AtIndex (0), sorted.Min ()) << "Min failed on a sorted list";
   EXPECT_EQ (unsorted.AtIndex (0), unsorted.Max ()) << "Max failed on an unsorted list";
   EXPECT_EQ (sorted.AtIndex (5), sorted.Max ()) << "Max failed on a sorted list";
   
}

TYPED_TEST_P (_hyListOrderableTest, SetOperationTests) {
  _hyListOrderable <TypeParam> evens,
                               odds, 
                               all,
                               empty,
                               holder;
                               
  for (unsigned long value = 0UL; value < 100UL; value++) {
    all.append ((TypeParam) value);
    if (value % 2) {
      odds.append ((TypeParam) value);
    } else {
      evens.append ((TypeParam) value);
    }
  }
  
  EXPECT_EQ (all, odds + evens)   << "UNION operation failed (odds + evens)";
  EXPECT_EQ (all, evens + odds)   << "UNION operation failed (evens + odds)";
  EXPECT_EQ (empty, odds * evens) << "INTERSECTION operation failed (odds * evens)";
  EXPECT_EQ (odds, odds - evens) << "DIFFERENCE operation failed (odds - evens)";
  EXPECT_EQ (evens, evens- odds)  << "DIFFERENCE operation failed (evens - odds)";
  EXPECT_EQ (all, odds % evens)   << "XOR operation failed (odds + evens)";
  EXPECT_EQ (0L, odds.CountCommonElements (evens)) << "CountCommonElements failed (odds, evens)";
  EXPECT_EQ (evens.countitems(), all.CountCommonElements (evens)) << "CountCommonElements failed (all, evens)";
  EXPECT_EQ (odds.countitems(), odds.CountCommonElements (all)) << "CountCommonElements failed (odds, all)";
  
  
  /*TypeParam array_sorted  [2] = {(TypeParam)505, (TypeParam)532},
            array_sorted2 [2] = {(TypeParam)511, (TypeParam)532};
            
  _hyListOrderable<long> index,
                         index2;
  
  _hyListOrderable <TypeParam> t1        (2UL, array_sorted),
                               t2        (2UL, array_sorted2);
  
  holder.Merge (&t1,&t2,&index,&index2);
  
  
  for (unsigned long ii = 0; ii < index.countitems(); ii++) {
    printf ("index[%ld] = %ld\n", ii, index.Element (ii));
  }

  for (unsigned long ii = 0; ii < index2.countitems(); ii++) {
    printf ("index2[%ld] = %ld\n", ii, index2.Element (ii));
  }
  ASSERT_EQ (index.countitems(), t1.countitems());
  ASSERT_EQ (holder.countitems(), 3UL);*/
  

  holder.Merge (&evens, &odds);
  EXPECT_EQ (all, holder) << "MERGE failed with (evens, odds)" 
            << this->dump_to_stream_as_longs (holder).getStr();
  holder.Merge (&odds, &evens);
  EXPECT_EQ (all, holder) << "MERGE failed with (odds, evens)" 
            << this->dump_to_stream_as_longs (holder).getStr();
            
            
            
  for (unsigned long samples = 0UL; samples < 1024L; samples++) {
      _hyListOrderable <TypeParam> x (this->make_random_list (genrand_int32() % 64, 100, 16)),
                                   y (this->make_random_list (genrand_int32() % 64, 100)),
                                   r1, 
                                   r2;
        
        x.Sort ();
        y.Sort ();
        r1 = x+y - (x%y);
        r2 = x*y;
        ASSERT_EQ  (r1, r2) << "X+Y - (X XOR Y) != X*Y " <<  this->dump_to_stream_as_longs (r1).getStr() << "; X = " 
          << this->dump_to_stream_as_longs (x).getStr() <<  "; Y = " << this->dump_to_stream_as_longs (y).getStr();
        r1 = (x-y)+(y-x); // symmetric difference
        r2 = x%y;
        ASSERT_EQ  (r1, r2) << "(X-Y)+(Y-X) != X%Y " << this->dump_to_stream_as_longs (r1).getStr() << "; X = " 
          << this->dump_to_stream_as_longs (x).getStr() <<  "; Y = " << this->dump_to_stream_as_longs (y).getStr();
        x.DeleteDuplicates ();
        y.DeleteDuplicates ();
        
        _hyListOrderable<long> index,
                               index2;
                               
        r1.Merge (&x,&y,&index, &index2);
        r2 = x+y;
        r2.DeleteDuplicates();
        
        
        ASSERT_EQ  (r1, r2) << "(X&&Y) != X+Y with duplicates removed " << this->dump_to_stream_as_longs (r1).getStr() << "; "
          << this->dump_to_stream_as_longs (r2).getStr() << "; X = " 
          << this->dump_to_stream_as_longs (x).getStr() <<  "; Y = " << this->dump_to_stream_as_longs (y).getStr();
          
        for (unsigned long i = 0L; i < index.countitems(); i++) {
        
           ASSERT_EQ (x.Element (i), r1.Element (index.Element (i))) << "Incorrect item index returned by Merge (1st list)" 
            << "[" << i << "]\n" << this->dump_to_stream_as_longs (x).getStr() << "\n" 
            << this->dump_to_stream_as_longs (y).getStr() << "\n" 
            << this->dump_to_stream_as_longs (r1).getStr() << "\n" << index.countitems() << "\n"
            << index.Element (i);
        } 

        for (unsigned long i = 0L; i < index2.countitems(); i++) {
        
           ASSERT_EQ (y.Element (i), r1.Element (index2.Element (i))) << "Incorrect item index returned by Merge (2nd list)" 
            << "[" << i << "]\n" << this->dump_to_stream_as_longs (x).getStr() << "\n" 
            << this->dump_to_stream_as_longs (y).getStr() << "\n" 
            << this->dump_to_stream_as_longs (r1).getStr() << "\n" << index2.countitems() << "\n"
            << index2.Element (i);
        } 
          
        x.FilterRange ((TypeParam)0L, (TypeParam)64L);
        y.FilterRange ((TypeParam)65L, (TypeParam)100L);
        
        ASSERT_EQ ((x*y).countitems(), 0UL) << "Non-overlapping range interestion expected to be empty";
  }
  
}


REGISTER_TYPED_TEST_CASE_P (_hyListOrderableTest, ConstuctorTests, SortingTests, InsertionAndSearchTests, MinMaxTest, SetOperationTests);

typedef ::testing::Types<char, long, double, _testOrderablePayload> _hyListOrderableTestTypes;

//typedef ::testing::Types<long> _hyListOrderableTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(_typedList, _hyListOrderableTest, _hyListOrderableTestTypes);
}
