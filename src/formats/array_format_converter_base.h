/*! @file array_format_converter_base.h
 *  @brief Base class for all raw frames format converters.
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

#ifndef SRC_FORMATS_ARRAY_FORMAT_CONVERTER_BASE_H_
#define SRC_FORMATS_ARRAY_FORMAT_CONVERTER_BASE_H_

#include "src/format_converter_base.h"

namespace sound_feature_extraction {

template <typename FIN, typename FOUT>
class ArrayFormatConverterBase : public FormatConverterBase<FIN, FOUT> {
 protected:
  virtual size_t OnInputFormatChanged(size_t buffersCount) override final {
    auto& outputFormat = FormatConverterBase<FIN, FOUT>::output_format_;
    auto& inputFormat = FormatConverterBase<FIN, FOUT>::input_format_;
    outputFormat->SetSize(inputFormat->Size());
    return buffersCount;
  }
};

}  // namespace sound_feature_extraction

#endif  // SRC_FORMATS_ARRAY_FORMAT_CONVERTER_BASE_H_
