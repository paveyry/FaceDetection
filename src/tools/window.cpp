//
// Created by hasb4k on 7/12/15.
//

#include "window.h"
#include "../features/two-horizontal-rectangles-feature.h"
#include "../features/two-vertical-rectangles-feature.h"
#include "../features/three-horizontal-rectangles-feature.h"
#include "../features/three-vertical-rectangles-feature.h"
#include "../features/four-rectangles-feature.h"
namespace violajones
{
  Window::Window(Point top, float r, std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image)
    : top_left(top), size_ratio(r), deviation{get_deviation(image, squared_image)},
      width((int)(WINDOW_WIDTH * r)), height((int)(WINDOW_HEIGHT * r))
  { }

  Window::Window(Point top, std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image)
    : Window(top, 1, image, squared_image)
  { }

  int Window::get_deviation(std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image)
  {
    auto nb_pixs = width * height;

    auto coords_a = top_left;
    auto coords_b = coords_a.translate(width, 0);

    auto coords_c = coords_a.translate(0, height);
    auto coords_d = coords_c.translate(width, 0);

    auto a = image->get_value(coords_a);
    auto b = image->get_value(coords_b);
    auto c = image->get_value(coords_c);
    auto d = image->get_value(coords_d);

    auto squared_a = squared_image->get_value(coords_a);
    auto squared_b = squared_image->get_value(coords_b);
    auto squared_c = squared_image->get_value(coords_c);
    auto squared_d = squared_image->get_value(coords_d);

    auto sum = d - (b + c) + a;
    auto squared_sum = squared_d - (squared_b + squared_c) + squared_a;
    auto avg = sum / nb_pixs;

    auto variance = squared_sum / nb_pixs - avg * avg;

    return variance > 0 ? (int) sqrt(variance) : 1;
  }

  Rectangle Window::to_rectangle()
  {
    return Rectangle{top_left, width, height};
  }

  std::vector<Window> Window::list_windows(std::shared_ptr<IntegralImage> image, std::shared_ptr<IntegralImage> squared_image)
  {
    std::vector<Window> windows;

    auto max_x = image->width;
    auto max_y = image->height;

    for (auto x = 0; x <= max_x; x += WINDOW_DX)
      for (auto y = 0; y <= max_y; y += WINDOW_DY)
      {
        auto max_width = image->width - x;
        auto max_height = image->height - y;

        auto width = WINDOW_WIDTH;
        auto height = WINDOW_HEIGHT;

        float ratio = 1;

        while (width <= max_width && height <= max_height)
        {
          windows.push_back(Window{Point{x, y}, ratio, image, squared_image});

          ratio *= WINDOW_SCALE;
          width = (int) (WINDOW_WIDTH * ratio);
          height = (int) (WINDOW_HEIGHT * ratio);
        }
      }

    return windows;
  }

  std::vector<std::shared_ptr<Feature>> Window::list_features()
  {
    std::vector<std::shared_ptr<Feature>> features = TwoHorizontalRectanglesFeature::list_features();

    std::vector<std::shared_ptr<Feature>> tmp = TwoVerticalRectanglesFeature::list_features();
    features.insert(features.end(), tmp.begin(), tmp.end());

    tmp = ThreeHorizontalRectanglesFeature::list_features();
    features.insert(features.end(), tmp.begin(), tmp.end());

    tmp = ThreeVerticalRectanglesFeature::list_features();
    features.insert(features.end(), tmp.begin(), tmp.end());

    tmp = FourRectanglesFeature::list_features();
    features.insert(features.end(), tmp.begin(), tmp.end());

    return features;
  }
}