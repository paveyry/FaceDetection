//
// Created by hasb4k on 7/12/15.
//

#ifndef FACE_RECOG_WINDOW_H
# define FACE_RECOG_WINDOW_H

# include <vector>
# include "point.h"
#include "rectangle.h"

#include "../image/integral-image.h"
#include "../features/feature.h"

namespace violajones
{
  class Window
  {
  public:
    Window(Point top, float ratio, IntegralImage image, IntegralImage squared_image);

    Window(Point top, IntegralImage image, IntegralImage squared_image);

    Rectangle to_rectangle();

    static std::vector<Window> list_windows(IntegralImage image, IntegralImage squared_image);

    static std::vector<Rectangle> list_features_positions(int min_width, int min_height);

    static std::vector<Feature> list_features();


  private:
    int get_deviation(IntegralImage image, IntegralImage squared_image);


  public:
    Point top_left;
    float ratio;
    float size_ratio;
    int deviation;
    int width;
    int height;
  };
}

#endif //FACE_RECOG_WINDOW_H
