/*! @file subband_energy.cc
 *  @brief Calculate the subband energy.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */

#include "src/transforms/subband_energy.h"
#include <math.h>
#ifdef __AVX__
#include <immintrin.h>
#include <simd/avx_extra.h>
#elif defined(__ARM_NEON__)
#include <arm_neon.h>  // NOLINT(build/include_order)
#endif
#include "src/primitives/energy.h"

namespace sound_feature_extraction {
namespace transforms {

using Primitives::WaveletFilterBank;

const std::vector<int> SubbandEnergy::kDefaultTreeFingerprint {
  3, 3, 3,
  4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6
};

SubbandEnergy::SubbandEnergy()
: treeFingerprint_(kDefaultTreeFingerprint) {
  RegisterSetter("tree", [&](const std::string& value) {
    treeFingerprint_ = WaveletFilterBank::ParseDescription(value);
    return true;
  });
}

size_t SubbandEnergy::OnFormatChanged(size_t buffersCount) {
  WaveletFilterBank::ValidateLength(treeFingerprint_,
                                    inputFormat_->Size());
  outputFormat_->SetSize(treeFingerprint_.size());
  return buffersCount;
}

void SubbandEnergy::Initialize() const {
  offsets_.reserve(treeFingerprint_.size());
  int offset = 0;
  for (auto depth : treeFingerprint_) {
    offsets_.push_back(offset);
    offset += (inputFormat_->Size() >> depth);
  }
  offsets_.push_back(offset);
}

void SubbandEnergy::Do(const float* in,
                       float* out) const noexcept {
  for (int i = 0; i < static_cast<int>(offsets_.size()) - 1; i++) {
    out[i] = calculate_energy(UseSimd(), in + offsets_[i],
                              offsets_[i + 1] - offsets_[i]);
  }
}

REGISTER_TRANSFORM(SubbandEnergy);

}  // namespace transforms
}  // namespace sound_feature_extraction
