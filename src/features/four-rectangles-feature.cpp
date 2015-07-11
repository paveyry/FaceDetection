//
// Created by hasb4k on 7/12/15.
//

#include "four-rectangles-feature.h"

namespace violajones
{

  FourRectanglesFeature::FourRectanglesFeature(Rectangle f)
    : frame{f}
  { }

  int FourRectanglesFeature::compute_value(Point win_top_left, float size_ratio, IntegralImage image)
  {
    Rectangle scaled_frame = frame.scale(size_ratio);
    Point top_left = scaled_frame.top_left.nested_point(win_top_left);
    int rects_width = scaled_frame.width / 2;
    int rects_height = scaled_frame.height / 2;

    auto coords_a = top_left;
    auto coords_b = coords_a.translate(rects_width, 0);
    auto coords_c = coords_b.translate(rects_width, 0);

    auto coords_d = coords_a.translate(0, rects_height);
    auto coords_e = coords_d.translate(rects_width, 0);
    auto coords_f = coords_e.translate(rects_width, 0);

    auto coords_g = coords_d.translate(0, rects_height);
    auto coords_h = coords_g.translate(rects_width, 0);
    auto coords_i = coords_h.translate(rects_width, 0);

    auto a = image.get_value(coords_a);
    auto b = image.get_value(coords_b);
    auto c = image.get_value(coords_c);
    auto d = image.get_value(coords_d);
    auto e = image.get_value(coords_e);
    auto f = image.get_value(coords_f);
    auto g = image.get_value(coords_g);
    auto h = image.get_value(coords_h);
    auto i = image.get_value(coords_i);

    auto sum_r1 = e - (b + d) + a;
    auto sum_r2 = f - (c + e) + b;
    auto sum_r3 = h - (e + g) + d;
    auto sum_r4 = i - (f + h) + e;

    return (int) (sum_r1 - sum_r2 - sum_r3 + sum_r4);

  }

  int FourRectanglesFeature::compute_value(IntegralImage image)
  {
    Point top_left{0, 0};
    return compute_value(top_left, 1f, image);
  }

  std::string FourRectanglesFeature::get_type()
  {
    return "FourRectanglesFeature";
  }
}