//
// Created by hasb4k on 7/12/15.
//

#include <memory>
#include <iostream>
#include "three-horizontal-rectangles-feature.h"
#include "../tools/window.h"

namespace violajones
{
  ThreeHorizontalRectanglesFeature::ThreeHorizontalRectanglesFeature(Rectangle f)
    : Feature(f)
  { }

  int ThreeHorizontalRectanglesFeature::compute_value(Point win_top_left, float size_ratio, std::shared_ptr<IntegralImage> image)
  {
    Rectangle scaled_frame = frame.scale(size_ratio);
    Point top_left = scaled_frame.top_left.nested_point(win_top_left);
    int rects_width = scaled_frame.width / 3;
    int rects_height = scaled_frame.height;


    auto coords_a = top_left;
    auto coords_b = coords_a.translate(rects_width, 0);
    auto coords_c = coords_b.translate(rects_width, 0);
    auto coords_d = coords_c.translate(rects_width, 0);

    auto coords_e = coords_a.translate(0, rects_height);
    auto coords_f = coords_e.translate(rects_width, 0);
    auto coords_g = coords_f.translate(rects_width, 0);
    auto coords_h = coords_g.translate(rects_width, 0);

    auto a = image->get_value(coords_a);
    auto b = image->get_value(coords_b);
    auto c = image->get_value(coords_c);
    auto d = image->get_value(coords_d);
    auto e = image->get_value(coords_e);
    auto f = image->get_value(coords_f);
    auto g = image->get_value(coords_g);
    auto h = image->get_value(coords_h);

    auto sum_r1 = f - (b + e) + a;
    auto sum_r2 = g - (c + f) + b;
    auto sum_r3 = h - (d + g) + c;

    return (int) (sum_r1 - sum_r2 + sum_r3);
  }

  int ThreeHorizontalRectanglesFeature::compute_value(std::shared_ptr<IntegralImage> image)
  {
    return compute_value(Point{0, 0}, 1, image);
  }

  std::string ThreeHorizontalRectanglesFeature::get_type()
  {
    return "ThreeHorizontalRectanglesFeature";
  }

  std::vector<std::shared_ptr<Feature>> ThreeHorizontalRectanglesFeature::list_features()
  {
    std::vector<std::shared_ptr<Feature>> features;
    for (auto& rect : Window::list_features_positions(min_width, min_height))
      features.push_back(std::make_shared<ThreeHorizontalRectanglesFeature>(rect));
    return features;
  }
}