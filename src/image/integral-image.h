//
// Created by hasb4k on 7/11/15.
//

#ifndef FACERECOG_INTEGRAL_IMAGE_H
# define FACERECOG_INTEGRAL_IMAGE_H

# include <SFML/Graphics.h>
# include <functional>
# include <vector>

# include "grey-image.h"

namespace violajones
{
  class IntegralImage
  {
  public:
    /* constructors */
    IntegralImage(GreyImage, std::function<long(byte)> type);

    IntegralImage(GreyImage);

    IntegralImage(sf::Image, std::function<long(byte)> type);

    IntegralImage(sf::Image);

    IntegralImage(std::string, std::function<long(byte)> type);

    IntegralImage(std::string);

  public:
    GreyImage image;
    std::function<long(byte)> type;
    std::vector<std::vector<long>> table;
    int width;
    int height;


  };
}

#endif /* !FACERECOG_INTEGRAL_IMAGE_H */
