//
// Created by veyry_p on 7/11/15.
//

#include <iostream>
#include <chrono>
#include <numeric>
#include "strong-classifier.h"
#define LEARN_PASS (400)

namespace violajones
{
  StrongClassifier::StrongClassifier(std::vector<WeakClassifier> classifiers)
          : classifiers{classifiers}
  {
    double galpha = 0;
    for (auto& classifier : classifiers)
      galpha += classifier.alpha_;
    global_alpha = galpha;
  }

  bool StrongClassifier::check(Window win, IntegralImage image)
  {
    double sumvalues = 0;
    for (auto& weakclass : classifiers)
      sumvalues += weakclass.get_value(win, image);
    return sumvalues >= global_alpha / 2.0;
  }

  void StrongClassifier::save(std::string path)
  {
    std::fstream fs;
    fs.open(path);
    for (auto& classif : classifiers)
      fs << classif.alpha_ << " "
      << classif.threshold_ << " "
      << classif.parity_ << " "
      << classif.feature_.get_type() << " "
      << classif.feature_.frame.top_left.x << " "
      << classif.feature_.frame.top_left.y << " "
      << classif.feature_.frame.width << " "
      << classif.feature_.frame.height << std::endl;
    fs.close();
  }

  StrongClassifier StrongClassifier::load_from_file(std::string path)
  {
    std::function<WeakClassifier(std::string)> restore_classifier =
            [](std::istringstream& s) {
              long alpha;
              int threshold;
              char parity;
              std::string feature_type;
              int featurex;
              int featurey;
              int featurewidth;
              int featureheight;
              s >> alpha >> threshold >> parity >> feature_type >> featurex >> featurey
                >> featurewidth >> featureheight;
              Rectangle feature_frame(Point(featurex, featurey), featurewidth, featureheight);
              Feature feature;
              if (feature_type == "FourRectanglesFeature")
                feature = FourRectangleFeature(feature_frame);
              else if (feature_type == "ThreeHorizontalRectanglesFeature")
                feature = ThreeHorizontalRectanglesFeature(feature_frame);
              else if (feature_type == "ThreeVerticalRectanglesFeature")
                feature = ThreeVerticalRectanglesFeature(feature_frame);
              else if (feature_type == "TwoHorizontalRectanglesFeature")
                feature = TwoHorizontalRectanglesFeature(feature_frame);
              else if (feature_type == "TwoVerticalRectanglesFeature")
                feature = TwoVerticalRectanglesFeature(feature_frame);
              else
                feature = TwoVerticalRectanglesFeature(feature_frame);
              return WeakClassifier(alpha, threshold, parity, feature);
            };
    std::ifstream infile(path);
    std::string line;
    std::vector<WeakClassifier> classifiers;
    while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      classifiers.push_back(restore_classifier(iss));
    }
    return StrongClassifier(classifiers);
  }

  StrongClassifier StrongClassifier::train(std::string tests_dir)
  {
    std::cout << "Initializing Trainer ...\n"
    << "Loading trainer tests ..." << std::endl;
    auto start = std::chrono::steady_clock::now();
    auto tests_set = load_tests_set(tests_dir);
    auto& tests = tests_set.first;
    auto& features_values = tests_set.second;

    unsigned long ncached_features;
    for (FeaturesValues& ftvalues : features_values)
      if (ftvalues.values.size)
        ++ncached_features;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Tests loaded in " << diff.count() << " seconds ("
    << ncached_features * 100 / features_values.size()
    << "% cached)\n Launching training..." << std::endl;

    std::vector<WeakClassifier> classifiers(LEARN_PASS);
    auto ipass = 1;
    while (ipass <= LEARN_PASS)
    {
      start = std::chrono::steady_clock::now();
      std::cout << ipass << "/" << LEARN_PASS << "trainer pass..." << std::endl;
      double weightsum = std::accumulate(tests.begin(), tests.end(), 0.0,
                                         [](double acc, TestImage& t){ return t.weight + acc; });
      double validweight = 0.0;
      for (auto i = 0; i < tests.size(); ++i)
      {
        tests[i].weight = tests[i].weight / weightsum;
        if (tests[i].valid)
          validweight += tests[i].weight;
      }
      TestWeakClassifier best(features_values[0], 0, 1, std::numeric_limits<double>::max());
      // TO PARALLELISE
      std::for_each(features_values.begin(), features_values.end(),
                    [&best](FeaturesValues& fv){
                      auto new_classifier = TestWeakClassifier.train(tests, validweight, fv);
                      if (best.errors > new_classifier.errors)
                        best = new_classifier;
                    });

      auto end = std::chrono::steady_clock::now();
      diff = end - start;
      std::cout << "New weak classifier selected in " << diff << " seconds (error score : " << best.errors << "\n"
              << "X: " << best.feature.feature.frame.top_left.x << " Y: " << best.feature.feature.frame.top_left.y
              << " - Width: " << best.feature.feature.frame.width << " Height: " << best.feature.feature.frame.height
              << std::endl;
      auto beta = best.errors / (1.0 - best.errors);
      if (beta < 1 / 100000000)
        beta = 1 / 100000000;

      for (FeatureValue& featurevalue : best.feature.values)
      {
        if (best.check(featurevalue.value) == tests[featurevalue.test_index].valid)
          tests[featurevalue.test_index].weight *= beta;
      }
    }


  }

  std::pair<std::vector<TestImage>,
          std::vector<FeaturesValues> > StrongClassifier::load_tests_set(std::string tests_dir)
  {
    return std::pair<vector < TestImage, allocator < TestImage>>, vector < FeatureValue, allocator < FeatureValue >> >
                                                                                         ();
  }

  std::vector<FeaturesValues> StrongClassifier::compute_features_values(std::vector<TestImage> tests)
  {
    return std::vector<FeaturesValues>();
  }

  ::violajones::StrongClassifier::GreyImage StrongClassifier::load_image(std::string imagepath)
  {
    return nullptr;
  }

  std::vector<GreyImage> StrongClassifier::load_images(std::string dir)
  {
    return std::vector<bool, _Alloc>();
  }

};