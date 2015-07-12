//
// Created by hasb4k on 7/12/15.
//

#ifndef FACE_RECOG_TWO_HORIZONTAL_RECTANGLES_FEATURE_H
# define FACE_RECOG_TWO_HORIZONTAL_RECTANGLES_FEATURE_H

# include "feature.h"

namespace violajones
{
  class TwoHorizontalRectanglesFeature : public Feature
  {
  public:
    TwoHorizontalRectanglesFeature(Rectangle frame);

    virtual int compute_value(Point win_top_left, float size_ratio, std::shared_ptr<IntegralImage> image) override;

    virtual int compute_value(std::shared_ptr<IntegralImage> image) override;

    virtual std::string get_type() override;

    static std::vector<std::shared_ptr<Feature>> list_features();

  public:
    static const int min_width = 2;
    static const int min_height = 1;
  };
}

#endif /* !FACE_RECOG_TWO_HORIZONTAL_RECTANGLES_FEATURE_H */
