//
// Created by veyry_p on 7/11/15.
//

#include "strong-classifier.h"

namespace violajones
{
  StrongClassifier::StrongClassifier(std::vector<WeakClassifier> classifiers)
          : classifiers{classifiers}
  {
    double galpha = 0;
    for (auto& classifier : classifiers)
      galpha += classifier.alpha;
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
    std::function<WeakClassifier(std::sring)> restore_classifier =
            [](std::string s) {
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
              Rectangle feature_frame(Point(featureX, featureY), featurewidth, featureheight);
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
      classifiers.push_back(restore_classifier(line));
    return StrongClassifier(classifiers);
  }

  StrongClassifier StrongClassifier::train(std::string tests_dir)
  {
    return violajones::StrongClassifier(std::vector<WeakClassifier>());
  }

  std::pair<std::vector<TestImage>,
          std::vector<FeatureValue> > StrongClassifier::load_tests_set(std::string tests_dir)
  {
    return std::pair<vector < TestImage, allocator < TestImage>>, vector < FeatureValue, allocator < FeatureValue >> >
                                                                                         ();
  }

  std::vector<FeatureValue> StrongClassifier::compute_features_values(std::vector<TestImage> tests)
  {
    return std::vector<FeatureValue>();
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