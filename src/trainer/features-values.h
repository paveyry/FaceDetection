//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_FEATURES_VALUES_H
#define FACERECOG_FEATURES_VALUES_H

#include <vector>
#include "feature-value.h"

namespace violajones
{
  class FeatureValues
  {
  public:

    FeatureValues(const Feature& feature,
                  const std::vector<FeatureValue>& values)
            : feature(feature), values(values)
    { }

  public:
    Feature feature;
    std::vector<FeatureValue> values;
  };
};

#endif /* !FACERECOG_FEATURES_VALUES_H */
