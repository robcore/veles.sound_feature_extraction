/*! @file unpack_rdft.cc
 *  @brief Tests for sound_feature_extraction::transforms::UnpackRDFT.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright © 2013 Samsung R&D Institute Russia
 *
 *  @section License
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 */


#include "src/transforms/unpack_rdft.h"
#include "tests/transforms/transform_test.h"

using sound_feature_extraction::formats::ArrayFormatF;
using sound_feature_extraction::BuffersBase;
using sound_feature_extraction::transforms::UnpackRDFT;

class UnpackRDFTTest : public TransformTest<UnpackRDFT> {
 public:
  int Size;

  void Initialize(int size) {
    Size = size;
    SetUpTransform(1, Size, 16000);
    for (int i = 0; i < Size; i++) {
      (*Input)[0][i] = i;
    }
    UnpackRDFT::Initialize();
  }
};

TEST_F(UnpackRDFTTest, DoReal) {
  Initialize(257);
  Do((*Input)[0], (*Output)[0]);
  for (int i = Size; i < (Size - 1) * 2; i++) {
    ASSERT_EQ(2 * (Size - 1) - i, (*Output)[0][i]);
  }
}

TEST_F(UnpackRDFTTest, DoComplex) {
  Initialize(258);
  Do((*Input)[0], (*Output)[0]);
  for (int i = Size; i < (Size - 2) * 2; i += 2) {
    ASSERT_EQ(2 * (Size - 2) - i, (*Output)[0][i]);
    ASSERT_EQ(2 * (Size - 2) - i + 1, (*Output)[0][i + 1]);
  }
}
