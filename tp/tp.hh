#ifndef TP_HH
# define TP_HH

# include <tbb/tbb.h>
# include <vector>
# include <iostream>
# include <SDL/SDL.h>
# include <mutex>

struct Video {
  unsigned      w, h;
  SDL_Surface  *scr;
  Uint32       *pixels;
  std::mutex    _lock;

  void waitnquit();

  Video(unsigned width, unsigned height) : w(width), h(height) {
    SDL_Init(SDL_INIT_EVERYTHING);
    scr = SDL_SetVideoMode(w,h,32,
                           SDL_ASYNCBLIT|SDL_HWSURFACE|SDL_DOUBLEBUF);
    pixels = (Uint32 *)scr->pixels;
    SDL_WM_SetCaption("Parallel Mandelbrot Set",NULL);
  }

  void blit(SDL_Surface *s, SDL_Rect off) {
    std::lock_guard<std::mutex> lock(_lock);
    SDL_BlitSurface(s,NULL,scr,&off);
    SDL_Flip(scr);
  }

  SDL_Surface *zone(const SDL_Rect& off) {
    return SDL_CreateRGBSurface
      (SDL_SWSURFACE,off.w,off.h,scr->format->BitsPerPixel,
       scr->format->Rmask, scr->format->Gmask,
       scr->format->Bmask, scr->format->Amask);
  }
};

void Video::waitnquit() {
  SDL_Event event;
  bool  quit = false;
  while (!quit) {
    SDL_WaitEvent(&event);
    quit = event.type == SDL_QUIT || event.type == SDL_KEYDOWN;
  }
  SDL_Quit();
}

// RAII style sub-surface
struct SubSurface {
  SDL_Rect              off;
  SDL_Surface          *sub;
  Uint32               *pixels;
  Video&                screen;

  SubSurface(Video& _scr, SDL_Rect _off) : off(_off), screen(_scr) {
    sub = screen.zone(off);
    pixels = (Uint32 *)sub->pixels;
  }

  ~SubSurface() {
    screen.blit(sub, off);
    SDL_FreeSurface(sub);
  }

  Uint32& operator() (Uint32 x, Uint32 y) {
    x -= off.x;
    y -= off.y;
    return pixels[(y * sub->w) + x];
  }

};

// Manage conversion from pixel coord to real plan coord
struct real_plan {

  Uint32        width;
  Uint32        height;
  double        centerX, centerY, sizeX, sizeY;

  real_plan(Uint32 w, Uint32 h, double cx, double cy, double sx, double sy) :
    width(w), height(h), centerX(cx), centerY(cy), sizeX(sx), sizeY(sy) {}

  double realX(Uint32 x) const {
    static const double minX = centerX - sizeX/2.0;
    return (x*sizeX/width) + minX;
  }

  double realY(Uint32 y) const {
    static const double minY = centerY - sizeY/2.0;
    return (height - y) * sizeY/height + minY;
  }
};

#endif /* !TP_HH */
