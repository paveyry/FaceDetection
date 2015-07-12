//
// Created by veyry_p on 7/12/15.
//

#ifndef FACE_RECOG_DETECTOR_H
#define FACE_RECOG_DETECTOR_H

#include "../image/integral-image.h"
#include "../trainer/strong-classifier.h"
#include "../tools/rectangle.h"

namespace violajones
{
  class Detector
  {
  public:
    Detector(std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image,
             StrongClassifier classifier)
            : image_(image), squared_image_(squared_image), classifier_(classifier)
    { }

    Detector(GreyImage image, StrongClassifier classifier)
            : image_(std::make_shared<IntegralImage>(image)),
              squared_image_(std::make_shared<IntegralImage>(image, [](byte pix) { return (long) pix * pix; })),
              classifier_(classifier)
    { }

    Detector(std::string filename, StrongClassifier classifier)
            : Detector(GreyImage(filename), classifier)
    { }

    Detector(sf::Image image, StrongClassifier classifier)
            : Detector(GreyImage(image), classifier)
    { }

    std::vector<Rectangle> detect();

  public:
    std::shared_ptr<IntegralImage> image_;
    std::shared_ptr<IntegralImage> squared_image_;
    StrongClassifier classifier_;
  };
}

#endif /* !FACE_RECOG_DETECTOR_H */
