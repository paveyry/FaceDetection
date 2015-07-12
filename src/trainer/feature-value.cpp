//
// Created by veyry_p on 7/11/15.
//

#include <stddef.h>
#include <algorithm>
#include "feature-value.h"

namespace violajones
{

  bool FeatureValue::operator==(const FeatureValue& other)
  {
    return this->value_ == other.value_;
  }

  bool FeatureValue::operator!=(const FeatureValue& other)
  {
    return this->value_ != other.value_;
  }

  bool FeatureValue::operator<=(const FeatureValue& other)
  {
    return this->value_ <= other.value_;
  }

  bool FeatureValue::operator<(const FeatureValue& other)
  {
    return this->value_ < other.value_;
  }

  bool FeatureValue::operator>=(const FeatureValue& other)
  {
    return this->value_ >= other.value_;
  }

  bool FeatureValue::operator>(const FeatureValue& other)
  {
    return this->value_ > other.value_;
  }

  std::vector<FeatureValue> FeatureValue::compute_all_values(std::vector<TestImage>& tests,
                                                             Feature& feature)
  {
    std::vector<FeatureValue> values;
    for (size_t i = 0; i < tests.size(); ++i)
    {
      auto feature_value = feature.compute_value(tests[i].image_);
      values.push_back(FeatureValue((short) i, Feature::normalize_feature(feature_value, tests[i].derivation_)));
    }
    return values;
  }

  std::vector<FeatureValue> FeatureValue::compute_all_values_sorted(std::vector<TestImage>& tests,
                                                                    Feature& feature)
  {
    auto values = compute_all_values(tests, feature);
    std::sort(values.begin(), values.end());
    return values;
  }
}