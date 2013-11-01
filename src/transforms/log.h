/*! @file log.h
 *  @brief Taking logarithm on the real values.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright 2013 Samsung R&D Institute Russia
 */

#ifndef SRC_TRANSFORMS_LOG_H_
#define SRC_TRANSFORMS_LOG_H_

#include "src/formats/single_format.h"
#include "src/transforms/common.h"

namespace sound_feature_extraction {
namespace transforms {

class LogTransformBase {
 public:
  LogTransformBase() noexcept;

 protected:
  enum LogBase {
    LOG_BASE_2,
    LOG_BASE_10,
    LOG_BASE_E
  };

  static const std::unordered_map<std::string, LogBase> kLogBaseMap;
  static const LogBase kDefaultLogBase;
  static std::string LogBaseToString(LogBase lb) noexcept;

  LogBase base_;
};

template <class F>
class LogBase : public virtual OmpUniformFormatTransform<F>,
                public LogTransformBase {
 public:
  LogBase() {
    this->RegisterSetter("base", [&](const std::string& value) {
      auto lbit = kLogBaseMap.find(value);
      if (lbit == kLogBaseMap.end()) {
        return false;
      }
      base_ = lbit->second;
      return true;
    });
  }

  OMP_TRANSFORM_PARAMETERS(
      TP("base", "Logarithm base (2, 10 or e).",
         LogBaseToString(kDefaultLogBase))
  )
};

template <class F>
class Log : public LogBase<F> {
 public:
  TRANSFORM_INTRO("Log",
                  "Takes the logarithm from each real value of the signal.")
};

class LogRaw : public Log<formats::ArrayFormatF> {
 protected:
  virtual void Do(const float* in, float* out) const noexcept override;

  void Do(bool simd, const float* input, int length,
          float* output) const noexcept;
};

class LogRawInverse : public OmpInverseUniformFormatTransform<LogRaw>,
                      public LogBase<formats::ArrayFormatF> {
 protected:
  virtual void Do(const float* in, float* out) const noexcept override;

  void Do(bool simd, const float* input, int length,
          float* output) const noexcept;
};

class LogSingle : public Log<formats::SingleFormatF> {
 protected:
  virtual void Do(const float& in, float* out) const noexcept override;
};

class LogSingleInverse : public OmpInverseUniformFormatTransform<LogSingle>,
                         public LogBase<formats::SingleFormatF> {
 protected:
  virtual void Do(const float& in, float* out) const noexcept override;
};

}  // namespace transforms
}  // namespace sound_feature_extraction
#endif  // SRC_TRANSFORMS_LOG_H_
