//
// Created by hasb4k on 7/11/15.
//

#ifndef FACE_RECOG_POINT_H
#define FACE_RECOG_POINT_H

#include <bits/stringfwd.h>

namespace violajones
{
  class Point
  {
  public:
    Point(int x, int y);

    Point nested_point(Point parent);

    Point translate(int dx, int dy);

    Point scale(float ratio);

    std::string to_string();

  public:
    int x;
    int y;
  };
}

#endif //FACE_RECOG_POINT_H
