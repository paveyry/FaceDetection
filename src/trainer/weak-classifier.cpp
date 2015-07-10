//
// Created by veyry_p on 7/11/15.
//

#include "weak-classifier.h"

double get_alpha() const
{
  return alpha_;
}

int get_threshold() const
{
  return threshold_;
}

char get_parity() const
{
  return parity_;
}

const Feature& get_feature_() const
{
  return feature_;
}

bool WeakClassifier::check(Window win,
                           IntegralImage image)
{
  auto feature_value = feature_.compute_value(win.top_left, win.size_ratio, image);
  int sized_value = feature_value / (win.size_ratio * win.size_ratio);
  auto normalized_value = Features.normalize_feature(sized_value, win.deviation);
  return parity_ * normalized_value < parity_ * threshold;
}

double WeakClassifier::get_value(Window win, IntegralImage image)
{
  return 0;
}