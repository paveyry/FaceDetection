// Mandelbrot

#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <iostream>
#include <mutex>
#include <SDL/SDL.h>
#include <tbb/task_scheduler_init.h>
#include "tbb/blocked_range2d.h"
#include "tbb/parallel_for.h"

const double    log_2  = log(2.0);
const double    bail   = 2;
const double    bail2  = bail * bail;
const double    loglog = log(log(bail));

struct Video {
  unsigned      w, h;
  SDL_Surface  *scr;
  Uint32       *pixels;
  std::mutex    _lock;

  void waitnquit();

  Video(unsigned width, unsigned height) : w(width), h(height) {
    SDL_Init(SDL_INIT_EVERYTHING);
    scr = SDL_SetVideoMode(w,h,32,
                           SDL_HWSURFACE
                           | SDL_ASYNCBLIT
                           | SDL_DOUBLEBUF
                           );
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

  void operator() (Uint32 x, Uint32 y, Uint32 c) {
    SDL_LockSurface(scr);
    std::cout << "(" << x << "," << y << ")" << std::endl;
    pixels[y * w + x] = c;
    SDL_UnlockSurface(scr);
    SDL_Flip(scr);
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

struct colors {
  Video&        screen;
  int           cp[5];

  Uint32 inner_gradient(Uint32 src, Uint32 dst, double fact) const {
    SDL_Surface        *scr = screen.scr;
    Uint8               sr, sg, sb, dr, dg, db;
    SDL_GetRGB(src, scr->format,&sr,&sg,&sb);
    SDL_GetRGB(dst, scr->format,&dr,&dg,&db);
    double              tmpr = fact*(dr-sr);
    double              tmpg = fact*(dg-sg);
    double              tmpb = fact*(db-sb);
    return SDL_MapRGB(scr->format, sr + tmpr, sg + tmpg, sb + tmpb);
  }

  Uint32 gradient(double d) const {
    double              fact = 4*d;
    SDL_Surface        *scr = screen.scr;
    if (!fact)
      return SDL_MapRGB(scr->format,0,0,0);
    unsigned    down = (unsigned)floor(fact), up = (unsigned)ceil(fact);
    return this->inner_gradient(cp[down], cp[up], fact - down);
  }

  colors(Video& v) : screen(v) {
    auto format = screen.scr->format;
    cp[0] = SDL_MapRGB(format, 127,   0, 127);
    cp[1] = SDL_MapRGB(format, 127, 127,   0);
    cp[2] = SDL_MapRGB(format,   0, 255,   0);
    cp[3] = SDL_MapRGB(format,   0, 127, 127);
    cp[4] = SDL_MapRGB(format,   0,   0, 255);
  }

};

static
double iterate(double xi, double yi, size_t max_iter) {
  double        x=xi, y=yi;
  size_t        i;
  /* if (obvious_in(x,y))
     return 0; */
  for (i=1; i<=max_iter && (x*x + y*y) <= bail2; ++i) {
    double      xtmp = x*x - y*y + xi;
    y = 2*x*y + yi;
    x = xtmp;
  }
  double esc = 0;
  if (i<=max_iter) {
    double      xtmp = x*x - y*y + xi;
    y = 2*x*y + yi;
    x = xtmp;
    xtmp = x*x - y*y + xi;
      y = 2*x*y + yi;
      x = xtmp;
      i += 2;
      double    modzn = sqrt(x*x + y*y);
      esc = (i - (log(log(modzn)))/log_2)/(max_iter + 2);
    }
  return esc;
}

struct Compute {

  const size_t          max_iter;
  Video&                screen;
  const real_plan&      real;
  const colors&         color;

  void operator()(const tbb::blocked_range2d<Uint16>& r) const {
    Sint16      rend = r.rows().end(), cend = r.cols().end();
    Sint16      rbeg = r.rows().begin(), cbeg = r.cols().begin();
    Uint16      w = rend - rbeg, h = cend - cbeg;
    SDL_Rect    off = {rbeg, cbeg, w, h};

    SubSurface  surf(screen, off);

    for (auto i = rbeg; i != rend; ++i) {
      double    cx = real.realX(i);
      for (auto j = cbeg; j != cend; ++j) {
        double  cy = real.realY(j);
        surf(i, j) =
          color.gradient(iterate(cx,cy,max_iter));
        // screen(i,j,color.gradient(iterate(cx,cy,max_iter)));
      }
    }
  }

  Compute(size_t mi, Video& v, const real_plan& rp, const colors& c)
    : max_iter(mi), screen(v), real(rp), color(c) {}

};

void ParallelMandel(size_t max, Video& screen, const real_plan& real) {
  tbb::parallel_for
    (tbb::blocked_range2d<Uint16>(0,screen.w, 0, screen.h),
     Compute(max, screen, real, colors(screen)));
}

void LinearMandel(size_t max, Video& screen, const real_plan& real) {
  Compute               comp(max, screen, real, colors(screen));
  comp(tbb::blocked_range2d<Uint16>(0,screen.w, 0, screen.h));
}

int main(int argc, char* argv[])
{
  tbb::task_scheduler_init      init;
  size_t                        iter;
  iter = argc>1?atoi(argv[1]):32;
  Uint32                w = 900, h;
  double                cx = -0.5, cy = 0.0, sx = 3, sy = 2;
  if (argc>5) {
      cx = atof(argv[2]);
      sx = atof(argv[3]);
      cy = atof(argv[4]);
      sy = atof(argv[5]);
    }
  h = w * (sy/sx);
  std::cout << w << " * " << h << std::endl;
  Video                 video(w,h);
  real_plan             real(w,h,cx,cy,sx,sy);

  ParallelMandel(iter,video,real);

  video.waitnquit();

  exit(0);
}
