//
// Created by veyry_p on 7/11/15.
//

#include <iostream>
#include "../config.h"
#include "weak-classifier.h"

namespace violajones
{
  bool WeakClassifier::check(Window win, std::shared_ptr<IntegralImage> image)
  {
    auto feature_value = feature_->compute_value(win.top_left, win.size_ratio, image);
    int sized_value = (int) (feature_value / (win.size_ratio * win.size_ratio));
    auto normalized_value = Feature::normalize_feature(sized_value, win.deviation);


    bool tmp = parity_ * normalized_value < parity_ * threshold_;

    if (Config::debug_classifier_check)
      std::cout << "WeakClassifier::check " << tmp << " Feature: " << feature_->get_type()
          << " - feature_value: " << feature_value
          << " sized_value: " << sized_value
          << " normalized_value: " << normalized_value << std::endl;
    return tmp;

  }

  double WeakClassifier::get_value(Window win, std::shared_ptr<IntegralImage> image)
  {
    return check(win, image) ? alpha_ : 0;
  }
}