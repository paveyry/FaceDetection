//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_WEAK_CLASSIFIER_H
#define FACERECOG_WEAK_CLASSIFIER_H

#include "../image/integral-image.h"

namespace violajones
{
  class WeakClassifier
  {
  public:

    WeakClassifier(double alpha, int threshold, signed char parity, const Feature feature)
            : alpha_{alpha}, threshold_{threshold}, parity_{parity}, feature_{feature}
    { }

    bool check(Window win, IntegralImage image);

    double get_value(Window win, IntegralImage image) const;

  public:
    double alpha_;
    int threshold_;
    char parity_;
    Feature feature_;
  };
}

#endif /* !FACERECOG_WEAK_CLASSIFIER_H */
