//
// Created by hasb4k on 7/11/15.
//

#include <iostream>
#include "integral-image.h"

namespace violajones
{
  IntegralImage::IntegralImage(GreyImage grey_image, std::function<long(byte)> type)
          : image{grey_image}, type{type}, width{grey_image.width}, height{grey_image.height}
  {
    compute_integral_image();
  }

  IntegralImage::IntegralImage(GreyImage grey_image)
          : IntegralImage(grey_image, [](byte b) { return b; })
  { }

  IntegralImage::IntegralImage(sf::Image sf_image, std::function<long(byte)> type)
          : IntegralImage(GreyImage{sf_image}, type)
  { }

  IntegralImage::IntegralImage(sf::Image sf_image)
          : IntegralImage(sf_image, [](byte b) { return b; })
  { }

  IntegralImage::IntegralImage(std::string string, std::function<long(byte)> type)
          : IntegralImage(GreyImage{string}, type)
  { }

  IntegralImage::IntegralImage(std::string path)
          : IntegralImage(path, [](byte b) { return b; })
  { }

  long IntegralImage::get_value(Point point)
  {
    if (point.x == 0 || point.y == 0)
      return 0;
    return table[point.x - 1][point.y - 1];
  }

  int IntegralImage::get_deviation()
  {
    int nb = width * height;
    long squared_sum = 0;
    for (int x = 0; x < width; x++)
      for (int y = 0; y < height; y++)
        squared_sum += image.pixels->getPixel(x, y).r; // r == g == b


    long avg = get_value(Point{width, height}) / nb;
    int variance = (int) (squared_sum / nb - avg * avg);
    return variance > 0 ? (int) std::sqrt(variance) : 1;
  }

  void IntegralImage::compute_integral_image()
  {
    for (auto i = 0; i < width; ++i)
      table.push_back(std::vector<long>(height));

    table[0][0] = type(image.pixels->getPixel(0, 0).r);
    for (int x = 1; x < width; ++x)
      table[x][0] = table[x - 1][0] + type(image.pixels->getPixel(x, 0).r);

    for (int y = 1; y < height; ++y)
      table[0][y] = table[0][y - 1] + type(image.pixels->getPixel(0, y).r);

    for (int y = 1; y < height; ++y)
      for (int x = 1; x < width; ++x)
        table[x][y] = table[x][y - 1] + table[x - 1][y] + type(image.pixels->getPixel(x, y).r) - table[x - 1][y - 1];
  }


}
