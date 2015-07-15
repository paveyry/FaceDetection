//
// Created by veyry_p on 7/11/15.
//

#ifndef FACE_RECOG_STRONG_CLASSIFIER_H
#define FACE_RECOG_STRONG_CLASSIFIER_H

#include <tuple>
#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics/Image.hpp>
#include <functional>
#include <algorithm>
#include <tbb/tbb.h>
#include "weak-classifier.h"
#include "feature-value.h"
#include "test-image.h"
#include "feature-values.h"
#include "../image/grey-image.h"
#include "../image/integral-image.h"
#include "../tools/window.h"
#include "test-weak-classifier.h"

namespace violajones
{
  class StrongClassifier
  {
  public:
    StrongClassifier(std::vector<WeakClassifier> classifiers);

    bool check(Window win, std::shared_ptr<IntegralImage> image);

    void save(std::string path);

    static StrongClassifier load_from_file(std::string path);

    static StrongClassifier train(std::string tests_dir);


  private:
    static std::pair<std::vector<TestImage>,
            std::vector<FeatureValues> > load_tests_set(std::string tests_dir);

    static std::vector<FeatureValues> compute_features_values(std::vector<TestImage> tests);

    static std::shared_ptr<GreyImage> load_image(std::string imagepath);

    static tbb::concurrent_vector<std::shared_ptr<GreyImage>> load_images(std::string dir);

  public:
    std::vector<WeakClassifier> classifiers_;
    long double global_alpha_;

  };
}

#endif /* !FACE_RECOG_STRONG_CLASSIFIER_H */
