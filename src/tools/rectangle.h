//
// Created by hasb4k on 7/11/15.
//

#ifndef FACE_RECOG_RECTANGLE_H
# define FACE_RECOG_RECTANGLE_H

# include <SFML/Graphics/Image.hpp>
#include <memory>
# include <string>
# include "point.h"

namespace violajones
{
  class Rectangle
  {
  public:
    Rectangle(Point top_left, int w, int h);

    Rectangle nested_rectange(Rectangle parent);

    Rectangle scale(float ratio);

    void draw(std::shared_ptr<sf::Image> image);

    std::string to_string();

  public:
    Point top_left;
    int width;
    int height;
  };

}

#endif /* !FACE_RECOG_RECTANGLE_H */
