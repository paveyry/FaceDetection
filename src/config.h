//
// Created by hasb4k on 7/12/15.
//

#ifndef FACE_RECOG_CONFIG_H
# define FACE_RECOG_CONFIG_H

#include <stdint.h>

class Config
{
public:
  /* INIT FUNCTION */
  static inline void init_verbose_debug(int verbose)
  {
    debug_detector_detect = verbose >= 1;
    debug_classifier_check = verbose >= 2;
  }

  static inline void init_learn_pass(int passes)
  {
    learn_pass = passes;
  }

  static inline void init_number_load(int nb)
  {
    number_load = nb;
  }

  static inline void set_parallelized()
  {
    parallelized = true;
  }

  /* WINDOW */
  static constexpr float window_scale = 1.25f;

  static constexpr int window_width = 24;
  static constexpr int window_height = 24;

  static constexpr int window_dx = 1;
  static constexpr int window_dy = 1;

  /* FEATURE */
  static constexpr int feature_dx = 1;
  static constexpr int feature_dy = 1;

  /* LEARNING */
  static unsigned learn_pass;
  static unsigned number_load;

  /* DEBUG */
  static int debug_detector_detect;
  static int debug_classifier_check;

  /* PARALLELIZE */
  static bool parallelized;

};

#endif //FACE_RECOG_CONFIG_H
