//
// Created by hasb4k on 7/11/15.
//

#include "features.h"

int normalize_feature(int value, int derivation)
{
  /* 40 is the average value of the derivation */
  return (value * 40) / derivation;
}
