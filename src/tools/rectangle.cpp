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

  void Rectangle::draw(sf::Image image)
  {
    /* FIXME */
  }

  std::string Rectangle::to_string()
  {
    return top_left.to_string() + " width: " +
            std::to_string(width) + " height: " + std::to_string(height);
  }
}