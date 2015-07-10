//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_FEATURE_VALUE_H
#define FACERECOG_FEATURE_VALUE_H

class FeatureValue
{
public:

  FeatureValue(short test_index_, int value)
          : test_index_(test_index_)
          , value(value)
  {}

  bool operator==(const FeatureValue& other);
  bool operator!=(const FeatureValue& other);
  bool operator<=(const FeatureValue& other);
  bool operator<(const FeatureValue& other);
  bool operator>=(const FeatureValue& other);
  bool operator>(const FeatureValue& other);
  

public:
  short test_index_;
  int value;
};

#endif /* !FACERECOG_FEATURE_VALUE_H */
