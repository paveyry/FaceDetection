//
// Created by veyry_p on 7/12/15.
//

#include "test-weak-classifier.h"

namespace violajones
{
  bool TestWeakClassifier::check(int featurevalue)
  {
    return parity_ * featurevalue < parity_ * threshold_;
  }

  WeakClassifier TestWeakClassifier::get_classifier(double alpha)
  {
    return WeakClassifier(alpha, threshold_, parity_, feature_.feature_);
  }

  TestWeakClassifier TestWeakClassifier::train(std::vector<TestImage>& tests, double validweight, FeatureValues& feature)
  {
    if (feature.values_.empty())
      feature.values_ = FeatureValue::compute_all_values(tests, *feature.feature_);

    auto positive_error = validweight;

    TestWeakClassifier best(feature, feature.values_[0].value_, 1, positive_error);

    for (size_t itest = 0; itest < feature.values_.size(); ++itest)
    {
      if (tests[feature.values_[itest].test_index_].valid_)
      {
        positive_error -= tests[feature.values_[itest].test_index_].weight_;

        if (positive_error < best.errors_)
          best = TestWeakClassifier(feature, feature.values_[itest].value_ + 1, 1, positive_error);
      }
      else
      {
        positive_error += tests[feature.values_[itest].test_index_].weight_;
        auto negative_error = 1.0 - positive_error;

        if (negative_error < best.errors_)
          best = TestWeakClassifier(feature, feature.values_[itest].value_ - 1, -1, negative_error);
      }
    }

    return best;
  }
}