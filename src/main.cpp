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

void print_usage(void)
{
  std::cout << "Usage:\n"
  << "./face-recog load <classifier_file> -i <image>\n"
  << "./face-recog train <training_dir> <output_classifier_path> [-i image]"
  << std::endl;
}

int main(int argc, char** argv)
{
  /*
  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }

      window.clear();
      window.draw(shape);
      window.display();
  }
  return 0;
  */
  /*
  std::string imagepath;
  std::string traindirpath;
  std::string method;
  std::string output_classifier;
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
          ("help,h", "Print help messages")
          ("method,m", po::value<std::string>(&method)->required(),"Select the method (load or train")
          ("image,i", po::value<std::string>(&imagepath)->required(), "Specify the input image")
          ("dir, d", po::value<std::string>(&traindirpath)->required(), "Specify the training dir")
          ("outclassif,o", po::value<std::string>(&output_classifier), "Specify the output classifier file");

  try
  {
    po::store(po::command_line_parser(argc, argv).options(desc))
  }*/
  //StrongClassifier classifier;

  auto classifier = StrongClassifier::load_from_file("/home/hasb4k/classifier");
  Detector detector{"/home/hasb4k/input.png", classifier};
  auto d = detector.detect();
  std::cout << d.size()<<std::endl;

  int i = 0;
  for (auto& rect : d)
  {
    std::cerr << "Curr i: " << i++ << " " << rect.to_string() << std::endl;
    rect.draw(detector.image_->image.pixels);
  }
  detector.image_->image.pixels->saveToFile("/home/hasb4k/output.png");
  return 0;
}
