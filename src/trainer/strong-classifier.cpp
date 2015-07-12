//
// Created by veyry_p on 7/11/15.
//

#include <iostream>
#include <chrono>
#include <numeric>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <boost/filesystem.hpp>
#include "strong-classifier.h"
#include "../features/four-rectangles-feature.h"

#define LEARN_PASS (400)
#define WINDOW_WIDTH (24)
#define WINDOW_HEIGHT (24)

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
      << classif.feature_->get_type() << " "
      << classif.feature_->frame.top_left.x << " "
      << classif.feature_->frame.top_left.y << " "
      << classif.feature_->frame.width << " "
      << classif.feature_->frame.height << std::endl;
    fs.close();
  }

  StrongClassifier StrongClassifier::load_from_file(std::string path)
  {
    std::function<WeakClassifier(std::istringstream&)> restore_classifier =
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
              if (feature_type == "FourRectanglesFeature")
              {
                return WeakClassifier(alpha, threshold, parity, std::make_shared<FourRectanglesFeature>(feature_frame));
              }
                /*
              else if (feature_type == "ThreeHorizontalRectanglesFeature")
                return WeakClassifier(alpha, threshold, parity, std::make_shared<ThreeHorizontalRectanglesFeature>(feature_frame));
              else if (feature_type == "ThreeVerticalRectanglesFeature")
                return WeakClassifier(alpha, threshold, parity, std::make_shared<ThreeVerticalRectanglesFeature>(feature_frame));
              else if (feature_type == "TwoHorizontalRectanglesFeature")
                return WeakClassifier(alpha, threshold, parity, std::make_shared<TwoHorizontalRectanglesFeature>(feature_frame));
              else if (feature_type == "TwoVerticalRectanglesFeature")
                return WeakClassifier(alpha, threshold, parity, std::make_shared<TwoVerticalRectanglesFeature>(feature_frame));
                 */
              return WeakClassifier(alpha, threshold, parity, std::make_shared<FourRectanglesFeature>(feature_frame));
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
    for (FeatureValues& ftvalues : features_values)
      if (ftvalues.values.size())
        ++ncached_features;
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Tests loaded in " << diff.count() << " seconds ("
    << ncached_features * 100 / features_values.size()
    << "% cached)\n Launching training..." << std::endl;

    std::vector<WeakClassifier> classifiers;
    auto ipass = 1;
    while (ipass <= LEARN_PASS)
    {
      start = std::chrono::steady_clock::now();
      std::cout << ipass << "/" << LEARN_PASS << "trainer pass..." << std::endl;
      double weightsum = std::accumulate(tests.begin(), tests.end(), 0.0,
                                         [](double acc, TestImage& t){ return t.weight + acc; });
      double validweight = 0.0;
      for (size_t i = 0; i < tests.size(); ++i)
      {
        tests[i].weight = tests[i].weight / weightsum;
        if (tests[i].valid)
          validweight += tests[i].weight;
      }
      TestWeakClassifier best(features_values[0], 0, 1, std::numeric_limits<double>::max());
      // TO PARALLELISE
      std::for_each(features_values.begin(), features_values.end(),
                    [&](FeatureValues& fv){
                      auto new_classifier = TestWeakClassifier.train(tests, validweight, fv);
                      if (best.errors > new_classifier.errors)
                        best = new_classifier;
                    });

      end = std::chrono::steady_clock::now();
      diff = end - start;
      std::cout << "New weak classifier selected in " << diff.count() << " seconds (error score : " << best.errors << "\n"
              << "X: " << best.feature.feature.frame.top_left.x << " Y: " << best.feature.feature.frame.top_left.y
              << " - Width: " << best.feature.feature.frame.width << " Height: " << best.feature.feature.frame.height
              << std::endl;
      auto beta = best.errors / (1.0 - best.errors);
      if (beta < 1 / 100000000)
        beta = 1 / 100000000;

      for (FeatureValue& featurevalue : best.feature.values)
        if (best.check(featurevalue.value) == tests[featurevalue.test_index].valid)
          tests[featurevalue.test_index].weight *= beta;

      auto alpha = std::log(1.0 / beta);
      classifiers.push_back(best.get_classifier(alpha));
      ++ipass;
    }
    std::cout << "Training finished" <<std::endl;
    return StrongClassifier(classifiers);
  }

  std::pair<std::vector<TestImage>,
            std::vector<FeatureValues> > StrongClassifier::load_tests_set(std::string tests_dir)
  {
    std::string gooddir = tests_dir + "/good";
    std::string baddir = tests_dir + "/bad";
    std::vector<GreyImage> good = load_images(gooddir);
    std::vector<GreyImage> bad = load_images(baddir);

    double goodweight = 1.0 / (2 * good.size());
    double badweight = 1.0 / (2 * bad.size());

    std::vector<TestImage> tests;
    for (size_t i = 0; i < good.size(); ++i)
      tests.push_back(TestImage(good[i], goodweight, true));

    for (auto i = good.size(); i < good.size() + bad.size(); ++i)
      tests.push_back(TestImage(bad[i - good.size()], badweight, false));
    auto features_values = compute_features_values(tests);
    return std::pair<std::vector<TestImage>, std::vector<FeatureValues> >(tests, features_values);
  }

  std::vector<FeatureValues> StrongClassifier::compute_features_values(std::vector<TestImage> tests)
  {
    std::vector<Feature> features = Window::list_features();
    std::vector<FeatureValues> features_values;
    for (size_t i = 0; i < features.size(); ++i)
    {
      auto values = FeatureValue::compute_all_values_sorted(tests, features[i]);
      features_values.push_back(FeatureValues(features[i], values));
    }
    return features_values;
  }

  GreyImage StrongClassifier::load_image(std::string imagepath)
  {
    sf::Image sfimage;
    sfimage.loadFromFile(imagepath);
    if (sfimage.getSize().x != WINDOW_WIDTH || sfimage.getSize().y != WINDOW_HEIGHT)
    {
      std::cerr << "Invalid test image size" << std::endl;
      exit(1);
    }
    return GreyImage(sfimage);
  }

  std::vector<GreyImage> StrongClassifier::load_images(std::string dir)
  {
    namespace fs = boost::filesystem;
    fs::path path(dir);
    fs::directory_iterator end_itr;
    std::vector<GreyImage> images;
    if (fs::exists(path) && fs::is_directory(path))
      for (fs::directory_iterator iter(path); iter != end_itr; ++iter)
        if (fs::is_regular_file(iter->status()))
          images.push_back(load_image(iter->path().string()));
    return images;
  }
}