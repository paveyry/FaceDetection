//
// Created by hasb4k on 7/11/15.
//

#ifndef FACERECOG_FEATURES_H
# define FACERECOG_FEATURES_H

# include <string>
# include "../tools/point.h"
# include "../image/integral-image.h"
# include "../tools/rectangle.h"

namespace violajones
{
  class Feature
  {
  protected:
    Feature(Rectangle f);

  public:
    virtual ~Feature() = default;

    virtual int compute_value(Point win_top_left, float size_ratio, std::shared_ptr<IntegralImage> image) = 0;

    virtual int compute_value(std::shared_ptr<IntegralImage> image) = 0;

    virtual std::string get_type() = 0;

    static int normalize_feature(int value, int derivation);

    // TODO ListFeatures

  public:
    Rectangle frame;

  };
}

#endif /* !FACERECOG_FEATURES_H */
