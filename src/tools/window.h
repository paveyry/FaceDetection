//
// Created by hasb4k on 7/12/15.
//

#ifndef FACE_RECOG_WINDOW_H
# define FACE_RECOG_WINDOW_H

# include <vector>
# include "point.h"
# include "rectangle.h"
# include "../image/integral-image.h"
# include "../features/feature.h"
# include "../config.h"

namespace violajones
{
  class Window
  {
  public:
    Window(Point top, float ratio, std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image);

    Window(Point top, std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image);

    Rectangle to_rectangle();

    static std::vector<Window> list_windows(std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image);

    static std::vector<Rectangle> list_features_positions(int min_width, int min_height);

    static std::vector<std::shared_ptr<Feature>> list_features();


  private:
    int get_deviation(std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image);


  public:
    Point top_left;
    float size_ratio;
    int width;
    int height;
    int deviation;
  };
}

#endif /* FACE_RECOG_WINDOW_H */
