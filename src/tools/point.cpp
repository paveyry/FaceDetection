//
// Created by hasb4k on 7/11/15.
//

#include <string>
#include "point.h"

namespace violajones
{
  Point::Point(int posX, int posY)
    : x{posX}, y{posY}
  { }

  Point Point::nested_point(Point parent)
  {
    return Point(x + parent.x, y + parent.y);
  }

  Point Point::translate(int dx, int dy)
  {
    return Point(x + dx, y + dy);
  }

  Point Point::scale(float ratio)
  {
    return Point((int)(x * ratio), (int)(y * ratio));
  }

  std::string Point::to_string()
  {
    return "X: " + std::to_string(x) + " Y: " + std::to_string(y);
  }
}
