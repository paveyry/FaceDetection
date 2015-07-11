//
// Created by veyry_p on 7/11/15.
//

#include "weak-classifier.h"

namespace violajones
{
  bool WeakClassifier::check(Window win, IntegralImage image)
  {
    auto feature_value = feature_->compute_value(win.top_left, win.size_ratio, image);
    int sized_value = feature_value / (win.size_ratio * win.size_ratio);
    auto normalized_value = Feature::normalize_feature(sized_value, win.deviation);
    return parity_ * normalized_value < parity_ * threshold_;
  }

  double WeakClassifier::get_value(Window win, IntegralImage image)
  {
    if (check(win, image))
      return alpha_;
    else
      return 0;
  }
}