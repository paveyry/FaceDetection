//
// Created by veyry_p on 7/11/15.
//

#include <stddef.h>
#include <algorithm>
#include "feature-value.h"

bool FeatureValue::operator==(const FeatureValue& other)
{
  return this->value == other.value;
}

bool FeatureValue::operator!=(const FeatureValue& other)
{
  return this->value != other.value;
}

bool FeatureValue::operator<=(const FeatureValue& other)
{
  return this->value <= other.value;
}

bool FeatureValue::operator<(const FeatureValue& other)
{
  return this->value < other.value;
}

bool FeatureValue::operator>=(const FeatureValue& other)
{
  return this->value >= other.value;
}

bool FeatureValue::operator>(const FeatureValue& other)
{
  return this->value > other.value;
}

std::vector<FeatureValue> FeatureValue::compute_all_values(std::vector<TestImage>& tests,
                                                           Feature feature)
{
  std::vector<FeatureValue> values(tests.size());
  for (size_t i = 0; i < tests.size(); ++i)
  {
    auto feature_value = feature.compute_value(tests[i].image);
    values[i] = FeatureValue::((short) i,
                               Features.normalize_feature(feature_value, tests[i].derivation));
  }
  return values;
}

std::vector<FeatureValue> FeatureValue::compute_all_values_sorted(std::vector<TestImage>& tests,
                                                                  Feature feature)
{
  auto values = compute_all_values(tests, feature);
  std::sort(values.begin(), values.end());
}