//
// Created by hasb4k on 7/11/15.
//

#include "grey-image.h"

namespace violajones
{
  GreyImage::GreyImage(sf::Image image)
  {
    pixels = std::make_shared<sf::Image>(image);
    create_pixels();
  }

  GreyImage::GreyImage(const std::string path)
  {
    pixels = std::make_shared<sf::Image>();
    pixels->loadFromFile(path);
    create_pixels();
  }

  void GreyImage::create_pixels()
  {
    auto size = pixels->getSize();
    width = size.x;
    height = size.y;

    for (int x = 0; x < width; ++x)
      for (int y = 0; y < height; ++y)
      {
        auto color = pixels->getPixel(x, y);
        sf::Uint8 grey = (sf::Uint8) (((int) color.r + color.g + color.b) / 3);
        pixels->setPixel(x, y, sf::Color{grey, grey, grey});
      }
  }
}
