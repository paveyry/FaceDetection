//
// Created by hasb4k on 7/11/15.
//

#ifndef FACE_RECOG_GREY_IMAGE_H
# define FACE_RECOG_GREY_IMAGE_H

#include <bits/stringfwd.h>
#include <SFML/Graphics/Image.hpp>
#include <memory>

typedef unsigned char byte;
typedef char sbyte;

namespace violajones
{
  class GreyImage
  {
  public:
    /* Constructors */
    GreyImage(sf::Image image);

    GreyImage(std::string path);

  protected:
    void create_pixels();


  public:

    std::shared_ptr<sf::Image> pixels;
    int width;
    int height;
  };

}

#endif /* FACE_RECOG_GREY_IMAGE_H */
