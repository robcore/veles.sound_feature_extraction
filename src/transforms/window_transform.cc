/*! @file window_transform.cc
 *  @brief New file description.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */

#include "src/transforms/window_transform.h"

namespace SpeechFeatureExtraction {

void WindowTransform::SetParameter(const std::string& name,
                                   const std::string& value){
  parameters_[name] = value;
}

}  // namespace SpeechFeatureExtraction
