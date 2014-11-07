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

//Generate necessary includes from the respective implementation file
#include "hy_avllist_reference.h"

namespace {
  
  // The fixture for testing class Foo.
  template <typename DATA>
  class _hyAVLListReferenceTest : public ::testing::Test {
    
  protected:
    
    _hyAVLListReferenceTest() {
      
    }
    
    virtual ~_hyAVLListReferenceTest() {
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
  
  TYPED_TEST_CASE_P(_hyAVLListReferenceTest);
  
  
  TYPED_TEST_P (_hyAVLListReferenceTest, CombinedTests) {
    _AVLListReference <TypeParam> empty;
    ASSERT_EQ (0UL, empty.Length()) << "An empty list has non-zero length";
    
    TypeParam * single_object = new TypeParam ("test string");
    
    _AVLListReference <TypeParam> single_item_list          (*single_object),
                                  another_single_item_list  (single_object);
    
    ASSERT_FALSE (single_object->SingleReference ()) << "Incorrect reference counting in single object constructor";
    ASSERT_EQ (single_item_list, another_single_item_list) << "A (X), B (X) did not result in A == B";
    
    _hyListReference<TypeParam> array_constructor_source;
    array_constructor_source.AppendNewInstance (new TypeParam ("one"));
    array_constructor_source.AppendNewInstance (new TypeParam ("two"));
    array_constructor_source.AppendNewInstance (new TypeParam ("three"));
    array_constructor_source.AppendNewInstance (new TypeParam ("five"));
    array_constructor_source.AppendNewInstance (new TypeParam ("seven"));
    
    // _AVLListReference <TypeParam> list_based (array_constructor_source);
    
    
     single_item_list = array_constructor_source;
    
     ASSERT_EQ (single_item_list.Length(), array_constructor_source.Length()) << "Dict ([a,b,...,x]) has different length than the argument list";
    
    _AVLListReference<TypeParam> stack_copy_list (single_item_list);

    ASSERT_EQ (single_item_list, stack_copy_list) << "Dict A = Dict B did not yield A == B";
    
    another_single_item_list.Clone (stack_copy_list);
    ASSERT_EQ (another_single_item_list, stack_copy_list) << "Dict A.Clone (Dict B) did not yield A == B";
    
    empty.Duplicate (&stack_copy_list);
    ASSERT_EQ (empty, stack_copy_list) << "Dict A.Duplicate (Dict B) did not yield A == B";
    
    _AVLListReference<TypeParam> * deep_copy = dynamic_cast
    <_AVLListReference<TypeParam> *>(stack_copy_list.DeepCopy());
    
    ASSERT_EQ (*deep_copy, stack_copy_list) << "Dict B = A.DeepCopy() did not yield A == B";
    
    BaseObj::DeleteObject(deep_copy);
    
    ASSERT_LE (0L, stack_copy_list.Delete (array_constructor_source (3))) << "Key expected to be present in a DICT is not there";
    ASSERT_GT (0L, stack_copy_list.Delete (array_constructor_source (3))) << "Key expected NOT to be present in a DICT IS there";
    
  }
  
  
  /*TYPED_TEST_P (_hyAVLListReferenceTest, LargeListTest) {
    _AVLListReference <TypeParam> largeList;
    
    for (unsigned long i = 0UL; i < (1<<20); i++) {
      largeList.Insert (new _String(_String::Random (10)));
    }
     
  }*/

  
  REGISTER_TYPED_TEST_CASE_P (_hyAVLListReferenceTest, CombinedTests/*, LargeListTest*/);
  
}

typedef ::testing::Types<_String> _hyAVLListReferenceTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(_typedList, _hyAVLListReferenceTest, _hyAVLListReferenceTestTypes);
