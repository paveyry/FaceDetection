//
// Created by veyry_p on 7/11/15.
//

#include "feature-value.h"

bool FeatureValue::operator==(const FeatureValue &other)
{
  return this->value == other.value;
}

bool FeatureValue::operator!=(const FeatureValue &other)
{
  return this->value != other.value;
}

bool FeatureValue::operator<=(const FeatureValue &other)
{
  return this->value <= other.value;
}

bool FeatureValue::operator<(const FeatureValue &other)
{
  return this->value < other.value;
}

bool FeatureValue::operator>=(const FeatureValue &other)
{
  return this->value >= other.value;
}

bool FeatureValue::operator>(const FeatureValue &other)
{
  return this->value > other.value;
}
