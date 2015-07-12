//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_WEAK_CLASSIFIER_H
#define FACERECOG_WEAK_CLASSIFIER_H

#include "../image/integral-image.h"
#include "../tools/window.h"
#include "../features/feature.h"
#include "../features/four-rectangles-feature.h"

namespace violajones
{
  class WeakClassifier
  {
  public:

    WeakClassifier(double alpha, int threshold, signed char parity, std::shared_ptr<Feature> feature)
            : alpha_{alpha}, threshold_{threshold}, parity_{parity}, feature_(feature)
    { }

    bool check(Window win, std::shared_ptr<IntegralImage> image);

    double get_value(Window win, std::shared_ptr<IntegralImage> image);

  public:
    double alpha_;
    int threshold_;
    char parity_;
    std::shared_ptr<Feature> feature_;
  };
}

#endif /* !FACERECOG_WEAK_CLASSIFIER_H */
