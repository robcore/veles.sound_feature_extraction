/*! @file int16_to_float.h
 *  @brief int16 to float converter.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */

#ifndef SRC_FORMATS_INT16_TO_FLOAT_H_
#define SRC_FORMATS_INT16_TO_FLOAT_H_

#include "src/formats/array_format.h"
#include "src/formats/array_format_converter_base.h"

namespace sound_feature_extraction {
namespace formats {

class Int16ToFloatRaw
    : public ArrayFormatConverterBase<ArrayFormat16, ArrayFormatF> {
 protected:
  virtual void Do(const int16_t* in,
                  float* out) const noexcept override;
};

}  // namespace formats
}  // namespace sound_feature_extraction
#endif  // SRC_FORMATS_INT16_TO_FLOAT_H_
