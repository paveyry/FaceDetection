//
// Created by hasb4k on 7/11/15.
//

#include "rectangle.h"
#include "point.h"
#include <string>

namespace violajones
{

  Rectangle::Rectangle(Point top, int w, int h)
    : top_left{top}, width{w}, height{h}
  { }

  Rectangle Rectangle::nested_rectange(Rectangle parent)
  {
    return Rectangle{top_left.nested_point(parent.top_left), width, height};
  }

  Rectangle Rectangle::scale(float ratio)
  {
    return Rectangle{top_left.scale(ratio), (int)(width * ratio),
                     (int)(height * ratio)};
  }

  void Rectangle::draw(std::shared_ptr<sf::Image> image)
  {
    for (auto x = top_left.x; x < top_left.x + width; ++x)
      for (auto y = top_left.y; y < top_left.y + height; ++y)
      {
        sf::Color color = image->getPixel(x, y);
        image->setPixel(x, y, sf::Color{(uint8_t)(color.r * 0.9), color.g, 255});
      }
  }

  std::string Rectangle::to_string()
  {
    return top_left.to_string() + " width: " +
            std::to_string(width) + " height: " + std::to_string(height);
  }
}
