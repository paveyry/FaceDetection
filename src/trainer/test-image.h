//
// Created by veyry_p on 7/11/15.
//

#ifndef FACE_RECOG_TEST_IMAGE_H
#define FACE_RECOG_TEST_IMAGE_H

namespace violajones
{
  class TestImage
  {
  public:
    TestImage(const IntegralImage& image, const bool valid, const int derivation, const double weight)
            : image(image), valid(valid), derivation(derivation), weight(weight)
    { }

  public:
    const IntegralImage image;
    const bool valid;
    const int derivation;
    double weight;
  };
};

#endif /* !FACE_RECOG_TEST_IMAGE_H */
