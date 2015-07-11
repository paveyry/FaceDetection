//
// Created by hasb4k on 7/11/15.
//

#include "integral-image.h"

namespace violajones
{
  IntegralImage::IntegralImage(GreyImage grey_image, std::function<long(byte)> type)
    : image{grey_image}, type{type}
  {
    width = grey_image.width;
    height = image.height;

  }

  IntegralImage::IntegralImage(GreyImage grey_image)
    : IntegralImage(grey_image, [](byte b) { return b; })
  { }

  IntegralImage::IntegralImage(sf::Image sf_image, std::function<long(byte)> type)
    : IntegralImage(GreyImage{sf_image}, type)
  { }

  IntegralImage::IntegralImage(sf::Image sf_image)
    : IntegralImage(sf_image, [](byte b) {return b; })
  { }

  IntegralImage::IntegralImage(std::string string, std::function<long(byte)> type)
    : IntegralImage(GreyImage{string}, type)
  { }

  IntegralImage::IntegralImage(std::string path)
    : IntegralImage(path, [](byte b) {return b; })
  { }
}
