#include "tp.hh"

#define BAIL2 4
#define MAX_ITER 15


int mandel(double x, double y)
{
  double        modz = x*x + y*y;
  double        zx = x, zy = y, tmp;
  size_t        i;
  for (i=0; modz <= BAIL2 && i < MAX_ITER; ++i)
    {
      tmp = zx*zx - zy*zy + x;
      zy = 2*zx*zy + y;
      zx = tmp;
      modz = x*x + y*y;
    }
   return i;
}

int main()
{
  tbb::blocked_range<size_t> r();
  return 0;
}
