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
  
  class _testPayload {
  public:
    
    _testPayload (void) { data = 0UL; unused = 0UL;}
    _testPayload (unsigned long p) { data = p; unused = 0UL; }
    _testPayload (const _testPayload& o) { data = o.data; unused = o.unused; }
    
    bool operator == (const _testPayload & o) const { return data == o.data;}
    
    operator unsigned long (void) {return data;}
    
    unsigned long data, unused;
  };
  
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
  
  
  TYPED_TEST_P (_hyAVLListReferenceTest, ConstuctorTests) {
  }
  
  

  
  REGISTER_TYPED_TEST_CASE_P (_hyAVLListReferenceTest, ConstuctorTests);
  
}

typedef ::testing::Types<_String> _hyAVLListReferenceTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(_typedList, _hyAVLListReferenceTest, _hyAVLListReferenceTestTypes);
