/*! @file intF_to_int32.h
 *  @brief float to int32 converter.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */

#ifndef SRC_FORMATS_FLOAT_TO_INT32_H_
#define SRC_FORMATS_FLOAT_TO_INT32_H_

#include "src/formats/array_format.h"
#include "src/formats/array_format_converter_base.h"

namespace sound_feature_extraction {
namespace formats {

class FloatToInt32Raw
    : public ArrayFormatConverterBase<ArrayFormatF, ArrayFormat32> {
 protected:
  virtual void Do(const float* in,
                  int32_t* out) const noexcept override;
};

}  // namespace formats
}  // namespace sound_feature_extraction
#endif  // SRC_FORMATS_FLOAT_TO_INT32_H_
