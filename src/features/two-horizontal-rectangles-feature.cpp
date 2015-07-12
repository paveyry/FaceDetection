//
// Created by hasb4k on 7/12/15.
//

#include "two-horizontal-rectangles-feature.h"

namespace violajones
{
  TwoHorizontalRectanglesFeature::TwoHorizontalRectanglesFeature(Rectangle f)
          : Feature(f)
  { }

  int TwoHorizontalRectanglesFeature::compute_value(Point win_top_left, float size_ratio, IntegralImage image)
  {
    Rectangle scaled_frame = frame.scale(size_ratio);
    Point top_left = scaled_frame.top_left.nested_point(win_top_left);
    int rects_width = scaled_frame.width / 2;
    int rects_height = scaled_frame.height;

    auto coords_a = top_left;
    auto coords_b = coords_a.translate(rects_width, 0);
    auto coords_c = coords_b.translate(rects_width, 0);

    auto coords_d = coords_a.translate(0, rects_height);
    auto coords_e = coords_d.translate(rects_width, 0);
    auto coords_f = coords_e.translate(rects_width, 0);

    auto a = image.get_value(coords_a);
    auto b = image.get_value(coords_b);
    auto c = image.get_value(coords_c);
    auto d = image.get_value(coords_d);
    auto e = image.get_value(coords_e);
    auto f = image.get_value(coords_f);

    auto sum_r1 = e - (b + d) + a;
    auto sum_r2 = f - (c + e) + b;

    return (int) (sum_r1 - sum_r2);
  }

  int TwoHorizontalRectanglesFeature::compute_value(IntegralImage image)
  {
    return compute_value(Point{0, 0}, 1, image);
  }

  std::string TwoHorizontalRectanglesFeature::get_type()
  {
    return "TwoHorizontalRectanglesFeature";
  }
}