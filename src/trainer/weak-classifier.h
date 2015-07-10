//
// Created by veyry_p on 7/11/15.
//

#ifndef FACERECOG_WEAK_CLASSIFIER_H
#define FACERECOG_WEAK_CLASSIFIER_H

namespace violajones
{
  class WeakClassifier
  {
  public:

    WeakClassifier(double alpha_, int threshold_, signed char byte,
                   long parity_, const Feature& feature_)
            : alpha_(alpha_), threshold_(threshold_), byte(byte), parity_(parity_), feature_(feature_)
    { }

    bool check(Window win, IntegralImage image);

    double get_value(Window win, IntegralImage image);

    double get_alpha() const
    {
      return alpha_;
    }

    int get_threshold() const
    {
      return threshold_;
    }

    char get_parity() const
    {
      return parity_;
    }

    const Feature& get_feature_() const
    {
      return feature_;
    }

  private:
    double alpha_;
    int threshold_;
    char parity_;
    Feature feature_;
  };
}

#endif /* !FACERECOG_WEAK_CLASSIFIER_H */
