//
// Created by veyry_p on 7/12/15.
//

#ifndef FACE_RECOG_TEST_WEAK_CLASSIFIER_H
#define FACE_RECOG_TEST_WEAK_CLASSIFIER_H

#include "feature-values.h"
#include "weak-classifier.h"


namespace violajones
{
  class TestWeakClassifier
  {
  public:
    TestWeakClassifier(FeatureValues feature, int threshold, char parity, double errors)
    : feature_(feature), threshold_(threshold), parity_(parity), errors_(errors)
    {}

    bool check(int featurevalue);

    WeakClassifier get_classifier(double alpha);

    static TestWeakClassifier train(std::vector<TestImage>& tests, double validweight, FeatureValues& feature);

  public:
    FeatureValues feature_;
    int threshold_;
    char parity_;
    double errors_;
  };
}

#endif /* !FACE_RECOG_TEST_WEAK_CLASSIFIER_H */
