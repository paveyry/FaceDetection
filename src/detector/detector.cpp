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
  std::vector<Rectangle> Detector::detect()
  {

    std::vector<Rectangle> rectvect;
    auto wins = Window::list_windows(image_, squared_image_);
    if (Config::debug_detector_detect)
      std::cout << "Windowlist :" << wins.size() << std::endl;


    static tbb::mutex mutex;
    if (Config::parallelized)
      tbb::parallel_for_each(wins.begin(), wins.end(), [&](Window &w) {
        if (classifier_.check(w, image_))
        {
          auto rect = w.to_rectangle();
          tbb::mutex::scoped_lock lock;
          lock.acquire(mutex);
          rectvect.push_back(rect);
          lock.release();
        }
      });
    else
      for (Window &w : wins)
        if (classifier_.check(w, image_))
          rectvect.push_back(w.to_rectangle());


    return rectvect;
  }
}