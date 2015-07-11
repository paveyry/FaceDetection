//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_FEATURES_VALUES_H
#define FACERECOG_FEATURES_VALUES_H

#include <vector>
#include "test-image.h"
#include "feature-value.h"
#include "../features/feature.h"

namespace violajones
{
  class FeatureValues
  {
  public:
    FeatureValues(Feature& pfeature, const std::vector<FeatureValue>& pvalues)
            : feature(pfeature), values{pvalues}
    { }

  public:
    Feature& feature;
    std::vector<FeatureValue> values;
  };
}

#endif /* !FACERECOG_FEATURES_VALUES_H */
