//
// Created by veyry_p on 7/9/15.
//

#include <SFML/Graphics.hpp>
#include "image/integral-image.h"
#include "detector/detector.h"
#include "trainer/strong-classifier.h"

using namespace violajones;

int main()
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
  auto classifier = StrongClassifier::load_from_file("/home/hasb4k/classifier");
  Detector detector{"/home/hasb4k/input.png", classifier};
  for (auto &rect : detector.detect())
    rect.draw(detector.image_->image.pixels);
  detector.image_->image.pixels->saveToFile("/home/hasb4k/output.png");
  return 0;
}
