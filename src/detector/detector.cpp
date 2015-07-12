//
// Created by veyry_p on 7/12/15.
//

#include "detector.h"

namespace violajones
{
  std::vector<Rectangle> Detector::detect()
  {
    std::function<Window(bool)> check = [](Window win){ return classifier_.check(win, image_); };
    std::vector<Rectangle> rectvect;
    for (Window* w : Window::list_windows(image_, squared_image_))
    {
      if (check(w))
        rectvect.push_back(w->to_rectangle());
    }
  }
}