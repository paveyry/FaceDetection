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
    : top_left(top), size_ratio(r), width((int)(Config::window_width * r)),
      height((int)(Config::window_height * r)), deviation(get_deviation(image, squared_image))
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

    auto max_x = image->width - Config::window_width;
    auto max_y = image->height - Config::window_height;

    for (auto x = 0; x <= max_x; x += Config::window_dx)
      for (auto y = 0; y <= max_y; y += Config::window_dy)
      {
        auto max_width = image->width - x;
        auto max_height = image->height - y;

        auto width = Config::window_width;
        auto height = Config::window_height;
        float ratio = 1.0f;

        while (width <= max_width && height <= max_height)
        {
          windows.push_back(Window(Point(x, y), ratio, image, squared_image));

          ratio *= Config::window_scale;
          width = (int) (Config::window_width * ratio);
          height = (int) (Config::window_height * ratio);
        }
      }

    return windows;
  }

  std::vector<Rectangle> Window::list_features_positions(int min_width, int min_height)
  {
    std::vector<Rectangle> positions;

    auto max_x = Config::window_width - min_width;
    auto max_y = Config::window_height - min_height;

    for (auto x = 0; x <= max_x; x += Config::feature_dx)
      for (auto y = 0; y <= max_y; y += Config::feature_dy)
      {
        int max_width = Config::window_width - x;
        for (auto width = min_width; width <= max_width; width += min_width)
        {
          int max_height = Config::window_height - y;
          for (auto height = min_height; height <= max_height; height += min_height)
            positions.push_back(Rectangle{Point{x, y}, width, height});
        }
      }

    return positions;
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