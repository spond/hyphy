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
#include "hy_dictionary.h"

namespace {
  
  // The fixture for testing class Foo.
  template <typename DATA>
  class _hyDictionaryTest : public ::testing::Test {
    
  protected:
    
    _hyDictionaryTest() {
      
    }
    
    virtual ~_hyDictionaryTest() {
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
  
  TYPED_TEST_CASE_P(_hyDictionaryTest);
  
  
  TYPED_TEST_P (_hyDictionaryTest, CombinedTestsSimpleKey) {
    _Dictionary <long,TypeParam> empty_dict;
    EXPECT_EQ  (0UL, empty_dict.Length()) << "Empty dictionary had a non-zero length";
    
    _Dictionary <long,TypeParam> single_element (0, 42L);
    EXPECT_EQ  (1UL, single_element.Length()) << "Single-element dictionary has the wrong length";
  }
  
  REGISTER_TYPED_TEST_CASE_P (_hyDictionaryTest, CombinedTestsSimpleKey);
  
}

typedef ::testing::Types<double, _String> _hyDictionaryTestTypes;
INSTANTIATE_TYPED_TEST_CASE_P(_typedList, _hyDictionaryTest, _hyDictionaryTestTypes);
