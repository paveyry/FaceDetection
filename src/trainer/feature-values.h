//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_FEATURE_VALUES_H
#define FACERECOG_FEATURE_VALUES_H

#include <vector>
#include "test-image.h"
#include "feature-value.h"
#include "../features/feature.h"

namespace violajones
{
  class FeatureValues
  {
  public:
    FeatureValues(std::shared_ptr<Feature> pfeature, const std::vector<FeatureValue>& pvalues)
            : feature_(pfeature), values_{pvalues}
    { }

  public:
    std::shared_ptr<Feature> feature_;
    std::vector<FeatureValue> values_;
  };
}

#endif /* !FACERECOG_FEATURE_VALUES_H */
