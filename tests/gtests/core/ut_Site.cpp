/*

HyPhy - Hypothesis Testing Using Phylogenies.

Copyright (C) 1997-now
Core Developers:
  Sergei L Kosakovsky Pond (spond@ucsd.edu)
  Art FY Poon    (apoon@cfenet.ubc.ca)
  Steven Weaver (sweaver@ucsd.edu)

Module Developers:
	Lance Hepler (nlhepler@gmail.com)
	Martin Smith (msmith@ucsd.edu)

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

#ifndef _HY_GENSITE_
#define _HY_GENSITE_

#include <iostream>
#include "gtest/gtest.h"
#include "site.h"
//#include <string>

using ::testing::TestWithParam;
using ::testing::Values;
using ::testing::Range;
using ::testing::Combine;

namespace {

// The fixture for testing class Foo.
class _SiteTest : public ::testing::Test {

  protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    _SiteTest() {
      // You can do set-up work for each test here.
    }

    virtual ~_SiteTest() {
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
  
  

    // Objects declared here can be used by all tests in the test case for Foo.
};

  void  DoConstructorTests (_Site& test, unsigned long exp_length, char const * val){
      EXPECT_EQ(exp_length, test.Length());
      EXPECT_EQ(HY_SITE_NULL_REFERENCE, test.GetRefNo());
      EXPECT_FALSE(test.IsComplete());
      test.SetRefNo(162L);
      EXPECT_FALSE(test.IsComplete());
      EXPECT_EQ(162, test.GetRefNo());
      if (val) {
          EXPECT_STREQ(val, test);
      }
      test.Complete();
      EXPECT_TRUE(test.IsComplete());
  }
  
TEST_F(_SiteTest, ConstructorsTest)
{
  // Normal
  _String test_s("hyphy");
  _Site test(test_s);
  
  DoConstructorTests (test, 5UL, "hyphy");
  

  test.Clear();
  test << "hyphy";
  DoConstructorTests (test, 5UL, "hyphy");

  _Site test3('h');
  DoConstructorTests (test3, 1UL, "h");

  long test_i = 162;
  _Site test4(test_i);
  EXPECT_EQ(0, test4.s_length);
  EXPECT_EQ(162, test4.GetRefNo());
  EXPECT_FALSE(test4.IsComplete());
  test4.SetRefNo(163);
  EXPECT_FALSE(test4.IsComplete());
  EXPECT_EQ(163, test4.GetRefNo());
  test4.Complete();
  EXPECT_TRUE(test4.IsComplete());
}

TEST_F(_SiteTest, CompleteTest)
{
  // Normal
  _Site test;
  EXPECT_FALSE(test.IsComplete());
  test.Complete();
  EXPECT_TRUE(test.IsComplete());
  test.SetRefNo(163);
  EXPECT_FALSE(test.IsComplete());
  test.Complete();
  EXPECT_TRUE(test.IsComplete());
}

TEST_F(_SiteTest, duplicateTest)
{
  // mod original
  _Site test (_String::Random (32)),
        test_duplicate,
        test_clone;
  
  test_clone.Clone (test);
  EXPECT_TRUE (test == test_clone && test.GetRefNo() == test_clone.GetRefNo()) <<
    "_Site.Clone(A) != A";

  test_duplicate.Duplicate (&test_clone);
  EXPECT_TRUE (test_duplicate == test_clone && test_duplicate.GetRefNo() == test_clone.GetRefNo()) <<
  "_Site.Duplicate(A) != A";

}

TEST_F(_SiteTest, clearTest)
{
  // Normal
  _Site test (_String::Random (32));
  test.Clear();
  EXPECT_EQ (0UL, test.Length()) << "Clear (A) did not set the length of A to 0";
  EXPECT_EQ (HY_SITE_NULL_REFERENCE, test.GetRefNo()) << "Clear (A) did not set the reference value to HY_SITE_NULL_REFERENCE";
}

TEST_F(_SiteTest, getRefNoTest)
{
  _Site test ;
  EXPECT_EQ(HY_SITE_NULL_REFERENCE, test.GetRefNo());
  test << (_String::Random (32));
  EXPECT_EQ(HY_SITE_NULL_REFERENCE, test.GetRefNo());
  test.Complete();
  EXPECT_EQ(HY_SITE_NULL_REFERENCE, test.GetRefNo());
  test.SetRefNo(162);
  EXPECT_EQ(162, test.GetRefNo());
  test.Complete();
  EXPECT_EQ(162, test.GetRefNo());
  EXPECT_TRUE(test.IsComplete());
}


} // namespace


#endif
