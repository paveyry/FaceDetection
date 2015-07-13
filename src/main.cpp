//
// Created by veyry_p on 7/9/15.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include "image/integral-image.h"
#include "detector/detector.h"
#include "trainer/strong-classifier.h"

using namespace violajones;
namespace po = boost::program_options;

void print_usage(void)
{
  std::cout << "Usage:\n"
  << "./face-recog load <classifier_file> -i <image>\n"
  << "./face-recog train <training_dir> <output_classifier_path> [-i image]"
  << std::endl;
}

static void load(po::variables_map& vm)
{
  auto classifier = StrongClassifier::load_from_file(vm["file"].as<std::string>());
  Detector detector{vm["image"].as<std::string>(), classifier};
  auto d = detector.detect();
  std::cout << d.size() << std::endl;

  int i = 0;
  for (auto& rect : d)
  {
    std::cerr << "Curr i: " << i++ << " " << rect.to_string() << std::endl;
    rect.draw(detector.image_->image.pixels);
  }
  std::shared_ptr<sf::Image> img = detector.image_->image.pixels;
  detector.image_->image.pixels->saveToFile(vm["saveimage"].as<std::string>());
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
        window.close();
      window.clear();
      window.draw(sprite);
      window.display();
    }
  }
}

static void train(po::variables_map& vm)
{

}

int main(int argc, char** argv)
{
  po::options_description desc("Options");
  desc.add_options()
          ("help,h", "Print help messages")
          ("method,m", po::value<std::string>(), "Select the method (load or train")
          ("image,i", po::value<std::string>(), "Specify the input image")
          ("dir,d", po::value<std::string>(), "Specify the training dir")
          ("saveimage,s", po::value<std::string>(), "Specify the output image name")
          ("classif,c", po::value<std::string>(), "Specify the classifier to use")
          ("outclassif,o", po::value<std::string>(), "Specify the output classifier file");

  try
  {
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);
    po::notify(vm);
    if (vm.count("help"))
      std::cout << desc << std::endl;
    else if (vm.count("method"))
    {
      if (vm["method"].as<std::string>() == "load")
      {
        if (!vm.count("file"))
          std::cout << "Please specify an input classifier" << std::endl;
        if (!vm.count("image"))
          std::cout << "Please specify an input image" << std::endl;
        load(vm);
      }
      else if (vm["method"].as<std::string>() == "train")
      {
        train(vm);
      }
      else
        std::cout << "Please specify an existing method" << std::endl;
    }
    else
    {
      std::cout << "Please specify a method" << std::endl;
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n" << desc << std::endl;
  }




  return 0;
}
