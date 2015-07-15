//
// Created by veyry_p on 7/12/15.
//

#include <iostream>
#include <tbb/tbb.h>
#include <chrono>
#include "../config.h"
#include "detector.h"

namespace violajones
{
  tbb::concurrent_vector<Rectangle> Detector::detect()
  {

    tbb::concurrent_vector<Rectangle> rectvect;
    auto wins = Window::list_windows(image_, squared_image_);
    if (Config::debug_detector_detect)
      std::cout << "Windowlist :" << wins.size() << std::endl;


    if (Config::parallelized)
      tbb::parallel_for_each(wins.begin(), wins.end(), [&](Window &w) {
        if (classifier_.check(w, image_))
          rectvect.push_back(w.to_rectangle());
      });
    else
      for (Window &w : wins)
        if (classifier_.check(w, image_))
          rectvect.push_back(w.to_rectangle());


    return rectvect;
  }
}