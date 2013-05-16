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

#include <tr1/tuple>
#include <iostream>
#include "gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//Generate necessary includes from the respective implementation file
#include "baseobj.h"
#include "list.h"
#include "matrix.h"
#include "datasetfilter.h"
#include "datasetfilternumeric.h"

namespace {

// The fixture for testing class Foo.
class _DataSetFilterNumericTest : public ::testing::Test {

protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  _DataSetFilterNumericTest() {
    // You can do set-up work for each test here.
    // Create objects of every type needed. Performance doesn't matter.

    FILEtest = fopen ("./tests/gtests/res/HIV_gp120.nex" , "r");

    longtest = new long();
    unsignedtest = new unsigned();
    _DataSetFilterNumerictest = new _DataSetFilterNumeric();
  }

  virtual ~_DataSetFilterNumericTest() {
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
    delete longtest;
    delete unsignedtest;
    delete _DataSetFilterNumerictest;
    fclose (FILEtest);
  }

  FILE* FILEtest;
  long* longtest;
  unsigned* unsignedtest;
  _DataSetFilterNumeric* _DataSetFilterNumerictest;
};


TEST_F(_DataSetFilterNumericTest, CompareTwoSitesTest) {

  //TODO
  //bool resultbool = _DataSetFilterNumerictest->CompareTwoSites(*longtest, *longtest);
  //EXPECT_EQ (resultbool, 0);

}


TEST_F(_DataSetFilterNumericTest, getProbabilityVectorTest) {

  _Parameter* result_Parameter = _DataSetFilterNumerictest->getProbabilityVector(*longtest, *longtest);
  //EXPECT_EQ (result_Parameter*, 0);

}


TEST_F(_DataSetFilterNumericTest, makeDynamicTest) {

  BaseRef resultBaseRef = _DataSetFilterNumerictest->makeDynamic();
  //EXPECT_EQ (resultBaseRef, 0);

}


}
