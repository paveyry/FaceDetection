//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_FEATURE_VALUE_H
#define FACERECOG_FEATURE_VALUE_H

#include <bits/stl_bvector.h>

class FeatureValue
{
public:

  FeatureValue(short test_index_, int value)
          : test_index(test_index_)
          , value(value)
  {}

  static std::vector<FeatureValue> compute_all_values(std::vector<TestImage>& tests, Feature feature);
  static std::vector<FeatureValue> compute_all_values_sorted(std::vector<TestImage>& tests, Feature feature);

  bool operator==(const FeatureValue& other);
  bool operator!=(const FeatureValue& other);
  bool operator<=(const FeatureValue& other);
  bool operator<(const FeatureValue& other);
  bool operator>=(const FeatureValue& other);
  bool operator>(const FeatureValue& other);

public:
  short test_index;
  int value;
};

#endif /* !FACERECOG_FEATURE_VALUE_H */
