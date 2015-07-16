//
// Created by veyry_p on 7/9/15.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include <chrono>
#include "image/integral-image.h"
#include "detector/detector.h"
#include "config.h"
#include "trainer/strong-classifier.h"

using namespace violajones;
namespace po = boost::program_options;

static int print_error_usage(std::string message, po::options_description& desc)
{
  std::cout << message << "\n" << desc << std::endl;
  return 1;
}

static void launch_detect(po::variables_map& vm, StrongClassifier& classifier)
{
  Detector detector{vm["image"].as<std::string>(), classifier};
  auto global_start = std::chrono::steady_clock::now();
  std::cout << "Beginning detection..." << std::endl;
  auto d = detector.detect();
  auto end = std::chrono::steady_clock::now();

  for (auto& rect : d)
    rect.draw(detector.image_->image.pixels);

  std::chrono::duration<double> duration = end - global_start;
  std::cout << "Detection done in " << duration.count() << " seconds." << std::endl;

  std::shared_ptr<sf::Image> img = detector.image_->image.pixels;
  detector.image_->image.pixels->saveToFile(vm["outimage"].as<std::string>());
  sf::RenderWindow window(sf::VideoMode(img->getSize().x, img->getSize().y), "Output image");
  sf::Texture texture;
  texture.loadFromImage(*img);
  sf::Sprite sprite(texture);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
        if (event.key.code == sf::Keyboard::Key::Escape)
          window.close();
      window.clear();
      window.draw(sprite);
      window.display();
    }
  }

}

static void load(po::variables_map& vm)
{
  auto classifier = StrongClassifier::load_from_file(vm["classif"].as<std::string>());
  launch_detect(vm, classifier);
}

static void train(po::variables_map& vm)
{
  auto classifier = StrongClassifier::train(vm["dir"].as<std::string>());
  std::cout << "Saving the classifier..." << std::endl;
  classifier.save(vm["saveclassif"].as<std::string>());

  std::cout << "Beginning face detection on image..." << std::endl;
  launch_detect(vm, classifier);
}

int main(int argc, char** argv)
{
  po::options_description desc("Options");
  desc.add_options()
          ("help,h", "Print help messages")
          ("method,m", po::value<std::string>()->default_value("load"), "Select the method (load or train)")
          ("image,i", po::value<std::string>(), "Specify the input image")
          ("dir,d", po::value<std::string>()->default_value("learning-tests"), "Specify the training dir")
          ("outimage,o", po::value<std::string>()->default_value("output.png"), "Specify the output image name")
          ("classif,c", po::value<std::string>(), "Specify the classifier to use")
          ("numberload,n", po::value<int>()->default_value(0), "Define the number of images to load")
          ("saveclassif,s", po::value<std::string>()->default_value("classif"), "Specify the output classifier file")
          ("verbose,v", po::value<int>()->default_value(0), "Define the verbose level (0, 1, 2)")
          ("passes,l", po::value<int>()->default_value(200), "Define the nomber of learning passes")
          ("para,p", "Activates parallelization");


  try
  {
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);
    Config::init_learn_pass(vm["passes"].as<int>());
    Config::init_verbose_debug(vm["verbose"].as<int>());
    Config::init_number_load(vm["numberload"].as<int>());
    if (vm.count("para"))
      Config::set_parallelized();
    if (vm.count("help"))
      std::cout << desc << std::endl;
    else if (vm.count("method"))
    {
      if (vm["method"].as<std::string>() == "load")
      {
        if (!vm.count("classif"))
          return print_error_usage("Please specify an input classifier", desc);
        if (!vm.count("image"))
          return print_error_usage("Please specify an input image", desc);
        load(vm);
      }
      else if (vm["method"].as<std::string>() == "train")
      {
        if (!vm.count("image"))
          return print_error_usage("Please specify an input image", desc);
        train(vm);
      }
      else
        return print_error_usage("Please specify an existing method", desc);
    }
    else
      return print_error_usage("Please specify a method", desc);
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n" << desc << std::endl;
  }
  return 0;
}
