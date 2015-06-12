#ifndef TP_HH
# define TP_HH

# include <tbb/tbb.h>
# include <vector>
# include <iostream>

struct Mytbbobj
{
public:
  double *data;
  void operator()(const tbb::blocked_range<size_t>& r) const;
};

#endif /* !TP_HH */
