//
// Created by hasb4k on 7/11/15.
//

#include "feature.h"

namespace violajones
{

  Feature::Feature(Rectangle f)
    : frame(f)
  { }

  int Feature::normalize_feature(int value, int derivation)
  {
    /* 40 is the average value of the derivation */
    return (value * 40) / derivation;
  }

}
