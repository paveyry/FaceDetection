//
// Created by veyry_p on 7/11/15.
//

#ifndef FACE_RECOG_TEST_IMAGE_H
#define FACE_RECOG_TEST_IMAGE_H

#include "../image/grey-image.h"
#include "../image/integral-image.h"

namespace violajones
{
  class TestImage
  {
  public:
    TestImage(GreyImage& gimage, const double weight, const bool valid)
            : image_(IntegralImage(gimage)), valid_(valid), weight_(weight)
    {
      //image_ = IntegralImage(gimage);
      derivation_ = image_.get_deviation();
    }

  public:
    IntegralImage image_;
    const bool valid_;
    int derivation_;
    double weight_;
  };
}

#endif /* !FACE_RECOG_TEST_IMAGE_H */
