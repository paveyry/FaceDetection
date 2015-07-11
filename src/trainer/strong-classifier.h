//
// Created by veyry_p on 7/11/15.
//

#ifndef FACE_RECOG_STRONG_CLASSIFIER_H
#define FACE_RECOG_STRONG_CLASSIFIER_H

#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include "weak-classifier.h"
#include "feature-value.h"
#include "test-image.h"
#include "features-values.h"

namespace violajones
{
  class StrongClassifier
  {
  public:
    StrongClassifier(std::vector<WeakClassifier> classifiers);

    bool check(Window win, IntegralImage image);

    void save(std::string path);

    static StrongClassifier load_from_file(std::string path);

    static StrongClassifier train(std::string tests_dir);


  private:
    static std::pair<std::vector<TestImage>,
            std::vector<FeatureValue> > load_tests_set(std::string tests_dir);

    static std::vector<FeatureValue> compute_features_values(std::vector<TestImage> tests);

    static GreyImage load_image(std::string imagepath);

    static std::vector<GreyImage> load_images(std::string dir);

  public:
    const std::vector<WeakClassifier> classifiers;
    double global_alpha;

  };
};

#endif /* !FACE_RECOG_STRONG_CLASSIFIER_H */
