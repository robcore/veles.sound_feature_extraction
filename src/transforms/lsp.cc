/*! @file lsp.cc
 *  @brief Converts Linear Prediction Coefficients (LPC) to more robust
 *  Line Spectral Pairs (LSP).
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

#include "src/transforms/lsp.h"
#include "src/primitives/lsp.h"

namespace sound_feature_extraction {
namespace transforms {

LSP::LSP() : intervals_(kDefaultIntervals), bisects_(kDefaultBisects) {
}

bool LSP::validate_intervals(const int& value) noexcept {
  return value >= 2;
}

bool LSP::validate_bisects(const int& value) noexcept {
  return value > 1;
}

void LSP::Do(const float* in, float* out) const noexcept {
  lpc_to_lsp(use_simd(), in, input_format_->Size(), bisects_,
             2.f / intervals_, out);
}

RTP(LSP, intervals)
RTP(LSP, bisects)
REGISTER_TRANSFORM(LSP);

}  // namespace transforms
}  // namespace sound_feature_extraction
