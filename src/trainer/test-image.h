//
// Created by veyry_p on 7/11/15.
//

#ifndef FACE_RECOG_TEST_IMAGE_H
#define FACE_RECOG_TEST_IMAGE_H

#include "../image/grey-image.h"

namespace violajones
{
  class TestImage
  {
  public:
    TestImage(const GreyImage& gimage, const double weight, const bool valid)
            : valid(valid), weight(weight)
    {
      image = IntegralImage(gimage);
      derivation = image.get_deviation();
    }

  public:
    IntegralImage image;
    const bool valid;
    int derivation;
    double weight;
  };
};

#endif /* !FACE_RECOG_TEST_IMAGE_H */
